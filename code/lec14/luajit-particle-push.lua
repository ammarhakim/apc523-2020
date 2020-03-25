local math = require("math")
local ffi = require("ffi")
local Time = require "Lib.Time"
local Alloc = require "Lib.Alloc"

require('jit.dump').start('bL', 'jit.log')
--jit.off()

ffi.cdef [[
typedef struct { double x[4], v[4]; } particle_t;
typedef struct { double c[3]; } vec3_t;
]]

-- metatable to handle vec3_objects
local mt = {
   __new = function (self)
      v = ffi.new("vec3_t")
      return v
   end,
   __index = function(self, idx) return self.c[idx] end,
   __newindex = function(self, idx, val) self.c[idx] = val end,
}
vec3 = ffi.metatype("vec3_t", mt)

function borisPush(q, m, dt, E, B, npart, pList)
   local qmdt = 0.5*q/m*dt
   local B_0, B_1, B_2 = B[0], B[1], B[2]
   local E_0, E_1, E_2 = E[0], E[1], E[2]

   local count = 0
   for pIdx = 1, npart do
      local ptcl = pList[pIdx]
      
      -- compute t and s vectors
      local t_0 = qmdt*B_0
      local t_1 = qmdt*B_1
      local t_2 = qmdt*B_2

      local tNorm = t_0*t_0 + t_1*t_1 + t_2*t_2
      local s_0 = 2*t_0/(1+tNorm)
      local s_1 = 2*t_1/(1+tNorm)
      local s_2 = 2*t_2/(1+tNorm)

      -- half-step electric field update
      local vm_0 = ptcl.v[0] + qmdt*E_0
      local vm_1 = ptcl.v[1] + qmdt*E_1
      local vm_2 = ptcl.v[2] + qmdt*E_2

      -- rotation around magnetic field
      -- (first compute cp = vm X t)
      local cp_0 =  vm_1*t_2 - vm_2*t_1;
      local cp_1 =  vm_2*t_0 - vm_0*t_2;
      local cp_2 =  vm_0*t_1 - vm_1*t_0;

      local vprime_0 = vm_0 + cp_0
      local vprime_1 = vm_1 + cp_1
      local vprime_2 = vm_2 + cp_2
      
      -- (first compute cp = vprime X s)
      cp_0 =  vprime_1*s_2 - vprime_2*s_1;
      cp_1 =  vprime_2*s_0 - vprime_0*s_2;
      cp_2 =  vprime_0*s_1 - vprime_1*s_0;

      local vp_0 = vm_0 + cp_0
      local vp_1 = vm_1 + cp_1
      local vp_2 = vm_2 + cp_2

      -- half-step electric field update: this gives final particle velocity
      ptcl.v[0] = vp_0 - qmdt*E_0
      ptcl.v[1] = vp_1 - qmdt*E_1
      ptcl.v[2] = vp_2 - qmdt*E_2

      ptcl.x[0] = ptcl.x[0] + dt*ptcl.v[0]
      ptcl.x[1] = ptcl.x[1] + dt*ptcl.v[1]
      ptcl.x[2] = ptcl.x[2] + dt*ptcl.v[2]

      count = count + 1
   end
   return count
end



E = vec3()
B = vec3()
B[2] = 1.0

qbym = 1.0
dt = qbym/4.0
nsteps = math.floor(2*math.pi/dt)

npart = 10000
ptclAlloc = Alloc.Alloc_meta_ctor(ffi.typeof("particle_t"))
plist = ptclAlloc(npart)
for i=1,npart do
   -- set position
   plist[i].x[0] = math.random()
   plist[i].x[1] = 0.0
   plist[i].x[2] = 0.0
   -- set velocity
   plist[i].v[0] = 0.0
   plist[i].v[1] = math.random()
   plist[i].v[2] = 0.0
end

count = 0
ntries = 10000

s = Time.clock()
-- push particles
for t = 1,ntries do
   nup = borisPush(1.0, 1.0, dt, E, B, npart, plist)
   count = count + nup
end
e = Time.clock()
print (string.format("Total particle updates %g million in %g", count/1e6, e-s))
