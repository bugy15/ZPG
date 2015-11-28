#include "ObjectLoader.h"


GLsizei ObjectLoader::loadObject(char * filename, GLuint &VAO){
	vec3 tang;
	ifstream in(filename, ios::in);
	if (!in) {
		printf("Cannot open file %s\n", filename);
		return false;
	}
	else printf("Open file %s \n", filename);



	string line;
	while (getline(in, line)) {

		if (line.substr(0, 2) == "v ") { //vertex
			istringstream s(line.substr(2));
			vec4 v; s >> v.x; s >> v.y; s >> v.z;
			vertices.push_back(v);
		}
		else if (line.substr(0, 2) == "vn") { //normal
			istringstream s(line.substr(2));
			vec3 v; s >> v.x; s >> v.y; s >> v.z;
			normals.push_back(v);
		}
		else if (line.substr(0, 2) == "vt") { //texture coordinate
			istringstream s(line.substr(2));
			vec2 v; s >> v.x; s >> v.y;
			uv.push_back(v);
		}
		else if (line.substr(0, 2) == "f ") { //face
			int pos;
			do {
				pos = line.find("/");
				if (pos != -1)  line.replace(pos, 1, " ");
			} while (pos != -1);


			istringstream s(line.substr(2));

			GLushort a, b, c, d, e, f, g, h, i;
			s >> a; s >> b; s >> c; s >> d; s >> e; s >> f; s >> g; s >> h; s >> i;
			a--; b--; c--; d--; e--; f--; g--; h--; i--;
			
			vec3 v1 = vec3(vertices[a].x, vertices[a].y, vertices[a].z);
			vec3 v2 = vec3(vertices[d].x, vertices[d].y, vertices[d].z);
			vec3 v3 = vec3(vertices[g].x, vertices[g].y, vertices[g].z);

			vec2 w1 = vec2(uv[b].x, uv[b].y);
			vec2 w2 = vec2(uv[e].x, uv[e].y);
			vec2 w3 = vec2(uv[h].x, uv[h].y);

			float x1 = v2.x - v1.x;
			float x2 = v3.x - v1.x;
			float y1 = v2.y - v1.y;
			float y2 = v3.y - v1.y;
			float z1 = v2.z - v1.z;
			float z2 = v3.z - v1.z;

			float s1 = w2.x - w1.x;
			float s2 = w3.x - w1.x;
			float t1 = w2.y - w1.y;
			float t2 = w3.y - w1.y;

			float r = 1.0f / (s1 * t2 - s2 * t1);
			vec3 sdir = vec3((t2 * x1 - t1 * x2) * r, (t2 * y1 - t1 * y2) * r, (t2 * z1 - t1 * z2) * r);
			vec3 tdir = vec3((s1 * x2 - s2 * x1) * r, (s1 * y2 - s2 * y1) * r, (s1 * z2 - s2 * z1) * r);

			Vertex v;
			v.Tangent[0] = sdir.x;
			v.Tangent[1] = sdir.y;
			v.Tangent[2] = sdir.z;
			v.Tangent[3] = 1.0f;

			v.Position[0] = vertices[a].x;
			v.Position[1] = vertices[a].y;
			v.Position[2] = vertices[a].z;
			v.uv[0] = uv[b].x;
			v.uv[1] = uv[b].y;
			v.Normal[0] = normals[c].x;
			v.Normal[1] = normals[c].y;
			v.Normal[2] = normals[c].z;

			data.push_back(v);

			v.Position[0] = vertices[d].x;
			v.Position[1] = vertices[d].y;
			v.Position[2] = vertices[d].z;
			v.uv[0] = uv[e].x;
			v.uv[1] = uv[e].y;
			v.Normal[0] = normals[f].x;
			v.Normal[1] = normals[f].y;
			v.Normal[2] = normals[f].z;
			
			data.push_back(v);

			v.Position[0] = vertices[g].x;
			v.Position[1] = vertices[g].y;
			v.Position[2] = vertices[g].z;
			v.uv[0] = uv[h].x;
			v.uv[1] = uv[h].y;
			v.Normal[0] = normals[i].x;
			v.Normal[1] = normals[i].y;
			v.Normal[2] = normals[i].z;
			
			data.push_back(v);
		}
		else if (line[0] == '#') { /* ignoring this line */ }
		else { /* ignoring this line */ }
	}

	
	printf("ObjectLoader: [%d] \n", data.size());
	glGenVertexArrays(1, &VAO); // generate the VAO
	glBindVertexArray(VAO); //bind the VAO
	glEnableVertexAttribArray(0); //enable vertex attributes
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	
	GLuint	VBO;
	glGenBuffers(1, &VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);  //generate the buffer objects
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(Vertex), &data.front(), GL_STATIC_DRAW); //bind the VBO to the VAO

	//set VAO attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(data[0]), (GLvoid*)0); //vertex
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(data[0]), (GLvoid*)sizeof(data[0].Position)); //normal
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(data[0]), (GLvoid*)24); //texture
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(data[0]), (GLvoid*)32); //tangent
	glBindVertexArray(0);
	
	return data.size();
}
