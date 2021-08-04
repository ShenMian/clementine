// Copyright 2021 SMS
// License(Apache-2.0)

#type vertex
#version 450 core

layout(location = 0) in vec3 a_Position;

void main()
{
	gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
}

#type fragment
#version 450 core

void main()
{
}
