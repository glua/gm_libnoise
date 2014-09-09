require "libnoise"
 -- The material ( a wireframe )
--local mat = Material("hunter/myplastic")
local mat = CreateMaterial("Terrain8", "VertexLitGeneric", {
	["$basetexture"] = "brick/brickwall031b",
	["$nocull"] = 1,
	["$model"] = 1
})
local mat = Material( "terrain.png")
local obj = Mesh() -- Create the IMesh object

verts = { -- A table of 3 vertices that form a triangle
	
}

function addQuad(q1, q2, q3, q4)
	q1 = q1 - Vector(2000, -1000, -1000)
	q2 = q2 - Vector(2000, -1000, -1000)
	q3 = q3 - Vector(2000, -1000, -1000)
	q4 = q4 - Vector(2000, -1000, -1000)

	//q1 q3 q4
	local a = q3 - q1;
	local b = q4 - q1;
	local normalA = a:Cross(b)
	normalA:Normalize()
	//q1 q2 q3
	local a = q2 - q1;
	local b = q3 - q1;
	local normalB = a:Cross(b)
	normalB:Normalize()

	//print(normalA)

	local c = Color(255, 255, 255)

	local colA = render.ComputeLighting(q1, normalA)*2
	local colB = render.ComputeLighting(q3, normalB)*2

	print(colA)

	colA = Color(colA.x*255, colA.y*255, colA.z*255)
	colB = Color(colB.x*255, colB.y*255, colB.z*255)

	//colA = Color(255, 255, 255)
	//colB = Color(255, 255, 255)



	verts = table.Add(verts, {
		{ pos = q1, u = 0, v = 0, normal = normalA, color = colA }, -- Vertex 1
		{ pos = q3, u = 1, v = 1, normal = normalA, color = colA }, -- Vertex 3
		{ pos = q4, u = 1, v = 0, normal = normalA, color = colA }, -- Vertex 2
		{ pos = q1, u = 0, v = 0, normal = normalB, color = colB }, -- Vertex 1
		{ pos = q2, u = 0, v = 1, normal = normalB, color = colB }, -- Vertex 3
		{ pos = q3, u = 1, v = 1, normal = normalB, color = colB }, -- Vertex 2
	})
end

function get(x, y, z)
	return NoiseTest(x, y)
end
local startTime = CurTime()

for x = -45, 45 do
	for y = -45, 45 do
		local xscale = x/30
		local yscale = y/30
		local scale = 1/30
		local xpos = x*50
		local ypos = y*50

		---local map = tree:getFunction("cave_shape_attenuate")
		//PrintTable(map)
		//print(map)
		local noise1 = get(xscale, yscale, 0) * 100
		local noise2 = get(xscale, yscale+scale, 0) * 100
		local noise3 = get(xscale+scale, yscale+scale, 0) * 100
		local noise4 = get(xscale+scale, yscale, 0) * 100
		
		//print(noise1)
		addQuad(Vector(xpos, ypos, noise1), Vector(xpos, ypos+50, noise2), Vector(xpos+50, ypos+50, noise3), Vector(xpos+50, ypos, noise4))
	end
end

local endTime = CurTime()

print(startTime)
print(endTime)

print("Time Taken: " .. (endTime - startTime))


obj:BuildFromTriangles( verts ) -- Load the vertices into the IMesh object

hook.Remove("PostDrawOpaqueRenderables", "IMeshTest")
hook.Add( "PostDrawOpaqueRenderables", "IMeshTest", function()
	--[[render.SuppressEngineLighting( true )
		 render.SetLightingMode( 0 )
	    render.SetLightingOrigin( Vector(-2216, -100, 2000))
	     render.ResetModelLighting( 0/255, 0/255, 0/255 )
		    render.SetColorModulation( 1,1,1 )
		    render.SetBlend( 1 )
		render.SetMaterial( mat ) -- Apply the material
		obj:Draw() -- Draw the mesh
		 render.SetLightingMode( 0 )
	render.SuppressEngineLighting(false)--]]
	render.SetMaterial( mat ) -- Apply the material
	obj:Draw() -- Draw the mesh
end )