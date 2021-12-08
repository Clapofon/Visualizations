#version 460

in vec4 color;
in vec2 fragmentUV;

out vec4 out_color;

uniform sampler2D sampler;


void main()
{
    float textureColor = texture2D(sampler, fragmentUV).a;

    out_color = vec4(color.rgb, textureColor);
}
