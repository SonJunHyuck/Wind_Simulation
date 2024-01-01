#version 430

layout(local_size_x = 256) in;

layout(location = 0) uniform int current_frame;
layout(location = 1) uniform float particle_res;
layout(location = 3) uniform int tail_length;
layout(location = 4) uniform sampler2D wind_texture;
layout(location = 5) uniform sampler2D particle_texture;

layout(std430, binding = 0) buffer iblock { float indices[]; };
layout(std430, binding = 1) buffer pblock { vec2 positions[]; };
layout(std430, binding = 2) buffer ablock { float ages[]; };
layout(std430, binding = 3) buffer lblock { float lifes[]; };
layout(std430, binding = 4) buffer tblock { vec2 tails[]; };
layout(std430, binding = 5) buffer tcblock { vec4 tail_colors[]; };

void main ()
{
   int index = int(gl_GlobalInvocationID);
   float delta = 1.0f / 60.0f;
   
   float particle_index = indices[index];
   float age = ages[index];
   float life = lifes[index];

   int index_tail = current_frame % tail_length;

   vec2 position;
   vec2 velocity;

   vec4 color = texture(particle_texture, vec2(fract(particle_index / particle_res), floor(particle_index / particle_res) / particle_res));

   vec2 particle_pos = vec2(
       color.r / 255.0 + color.b,
       color.g / 255.0 + color.a);

   if(age == 0)
   {
        position = vec2(2.0 * particle_pos.x - 1.0, 1.0 - 2.0 * particle_pos.y);
   }
   else
   {
        position = positions[index];
        tails[tail_length * index + index_tail] = position;
   }

   if(life < age)
   {
        position = vec2(2.0 * particle_pos.x - 1.0, 1.0 - 2.0 * particle_pos.y);
        age = 0;
   }

   velocity = texture(wind_texture, position).xy;

   float opacity = age / life;
   tail_colors[tail_length * index + index_tail] = vec4(length(velocity), length(velocity), 1 - length(velocity), min(1, 0.5f + opacity));

   velocity -= vec2(0.5f, 0.5f);
   velocity *= delta * delta * 32;
   age += delta * 20;

   positions[index] = position + velocity.xy;
   ages[index] = 0;
}