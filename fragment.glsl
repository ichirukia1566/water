uniform int initialized;
uniform sampler2D texUnit;
uniform float t;
uniform vec2 ct[3];
uniform float freq[3];
uniform float speed[3];
uniform float amp[3];
uniform vec2 island;
uniform vec3 light;

void init()
{
	
}

void update()
{
	vec2 texCoord = gl_TexCoord[0].xy;
	float height = 0.0;
	vec3 n = vec3(0.0, 0.0, 1.0); // normal, given by (-d(H(x, y, t))/dx, -d(H(x, y, t))/dy, 1)
	for (int i = 0; i < 3; ++i) {
	    // D_i(x, y) = ((x, y) - C_i) / |(x, y) - C_i| for circular waves
		float dx = texCoord.x - ct[i].x;
		float dy = texCoord.y - ct[i].y;
		float dist = sqrt(dx * dx + dy * dy);
		float dirX = dx / dist;
		float dirY = dy / dist;
		//float d = texCoord.x * dirX + texCoord.y * dirY;
		// H(x, y, t) = Sum(A_i * sin(D_i(x, y) * w_i + t * phi_i)) 
		// -> D_i(x, y) should be the distance
		height += amp[i] * sin(dist * freq[i] - t * speed[i] * freq[i]);

		// d(H(x, y, t))/dx = Sum(w_i * D_i.x * A_i * cos(D_i(x, y) * w_i + t * phi_i)) 
		// -> D_i(x, y) should be the distance
		// so the partial derivative is indeed dirX/dirY
		//float partialDerivX = (2.0 * texCoord.x - ct[i].x) / dist - dx * (texCoord.x * dx + texCoord.y * dy) / sqrt((dx * dx + dy * dy) * (dx * dx + dy * dy) * (dx * dx + dy * dy));
		//float partialDerivY = (2.0 * texCoord.y - ct[i].y) / dist - dy * (texCoord.x * dx + texCoord.y * dy) / sqrt((dx * dx + dy * dy) * (dx * dx + dy * dy) * (dx * dx + dy * dy));
		n.x -= freq[i] * dirX * amp[i] * cos(dist * freq[i] - t * speed[i] * freq[i]);
		n.y -= freq[i] * dirY * amp[i] * cos(dist * freq[i] - t * speed[i] * freq[i]);
		
	}
	vec2 island_dir = gl_TexCoord[0].xy - island; // vector from a pixel to center of normal distribution
	float sigma = 0.1;
	float island_height = (2.0 / sqrt(2.0 * 3.14159265 * sigma * sigma)) 
						* exp(-length(island_dir) * length(island_dir)
						/ (2.0 * sigma * sigma)) - 3.5; // using bivariate normal distribution
	if (island_height <= height) {
		float diff = max(0.0, dot(normalize(n), normalize(light))); // diffusion
		gl_FragColor = vec4(clamp(diff * 0.25 + 0.75, 0.0, 1.0), clamp(diff * 0.25 + 0.75, 0.0, 1.0), 1.0, 0.3);
	} else {
		gl_FragColor = vec4(1.0 - clamp(island_height * 0.08, 0.0, 1.0), 1.0, 1.0 - clamp(island_height * 0.08, 0.0, 1.0), 0.3);
	}
}


void main()
{
	if (initialized == 0) {
		init();
	} else {
		update();
	}
}