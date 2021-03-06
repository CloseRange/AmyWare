
#type vertex
#version 450
			
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TexCoord;
layout(location = 3) in float a_TexIndex;
layout(location = 4) in float a_TileFactor;

uniform mat4 u_ViewProjection;

out vec2 v_TexCoord;
out vec4 v_Color;
out flat float v_TexIndex;
out float v_TileFactor;

void main() {
	v_Color = a_Color;
	v_TexCoord = a_TexCoord;
	v_TexIndex = a_TexIndex;
	v_TileFactor = a_TileFactor;
	gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
}

#type fragment
#version 450
			
layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in vec4 v_Color;
in flat float v_TexIndex;
in float v_TileFactor;

uniform sampler2D u_Textures[32];

void main() {
	color = texture(u_Textures[int(v_TexIndex)], v_TexCoord * v_TileFactor) * v_Color;
}
