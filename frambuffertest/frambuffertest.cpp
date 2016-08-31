// frambuffertest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

class GL{
public:
	GLuint vao, vbo, nbo, vshader, fshader, shaderprogram, ebo, colorbuffer;
	GLint success;
	GLchar infolog[512];
	vector<vec3> vertexbuffer;

	void creatProgram(char* vs, char* fs){
		vshader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vshader, 1, &vs, NULL);
		glCompileShader(vshader);
		glGetShaderiv(vshader, GL_COMPILE_STATUS, &success);
		if (!success){
			glGetShaderInfoLog(vshader, 512, NULL, infolog);
			fprintf_s(stderr, "vshader:%s", infolog);
		}

		fshader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fshader, 1, &fs, NULL);
		glCompileShader(fshader);
		glGetShaderiv(fshader, GL_COMPILE_STATUS, &success);
		if (!success){
			glGetShaderInfoLog(fshader, 512, NULL, infolog);
			fprintf_s(stderr, "fshader:%s", infolog);
		}

		shaderprogram = glCreateProgram();
		glAttachShader(shaderprogram, vshader);
		glAttachShader(shaderprogram, fshader);
		glLinkProgram(shaderprogram);
		glGetProgramiv(shaderprogram, GL_LINK_STATUS, &success);
		if (!success){
			glGetProgramInfoLog(shaderprogram, 512, NULL, infolog);
			fprintf_s(stderr, "shaderprogram:%s", infolog);
		}
		glGetProgramiv(shaderprogram, GL_ACTIVE_UNIFORMS, &success);
		printf_s("number:%d\n", success);
		glDetachShader(shaderprogram, vshader);
		glDetachShader(shaderprogram, fshader);
	}

	GL(){}
	GLuint get_vao(){
		return vao;
	}

	GLuint get_program(){
		return shaderprogram;
	}
};


GLfloat cubeVertices[] = {
	// Positions          // Texture Coords
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
	-0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

	-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
	-0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
	-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

	0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
	0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
	-0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f
};

GLfloat quadVertices[] = {   // Vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
	// Positions   // TexCoords
	-1.0f, 1.0f, 0.0f, 1.0f,
	-1.0f, -1.0f, 0.0f, 0.0f,
	1.0f, -1.0f, 1.0f, 0.0f,

	-1.0f, 1.0f, 0.0f, 1.0f,
	1.0f, -1.0f, 1.0f, 0.0f,
	1.0f, 1.0f, 1.0f, 1.0f
};

GLfloat skyboxVertices[] = {
	// Positions          
	-1.0f, 1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,

	-1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f,

	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f,

	-1.0f, 1.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, 1.0f
};

static const char* vertexshadersource0 =
"#version 440 core\n"
"layout(location = 0) in vec3 vertexPosition_modelspace;\n"
"layout(location = 1) in vec2 texCoords;\n"

"uniform mat4 projection;\n"
"uniform mat4 view;\n"
"uniform mat4 model;\n"

"out vec2 Texcoords;\n"

"void main(){\n"
"gl_Position = projection * view * model * vec4(vertexPosition_modelspace,1.0f);\n"
"Texcoords=vec2(texCoords.s,1-texCoords.t);\n"
"}"
;

static const char* fragshadersource0 =
"#version 440 core\n"
"out vec4 color;\n"

"in vec2 Texcoords;\n"

"uniform sampler2D Texture;\n"

"void main(){\n"
"color = texture(Texture,Texcoords);\n"
"float average = (color.r + color.g + color.b) / 3.0;\n"
"color = vec4(average, average, average, 1.0); \n"
//"color=vec4(1);\n"
"}"
;

static const char* vertexshadersource1 =
"#version 440 core\n"
"layout(location = 0) in vec3 vertexPosition_modelspace;\n"

"uniform mat4 projection;\n"
"uniform mat4 view;\n"
"uniform mat4 model;\n"
"uniform mat4 transform;\n"

"out vec3 Texcoords;\n"

"void main(){\n"
"vec4 pos=projection * view * vec4(vertexPosition_modelspace,1.0f);\n"
"gl_Position = pos.xyww;\n"
"Texcoords=vertexPosition_modelspace;\n"
"}"
;

static const char* fragshadersource1 =
"#version 440 core\n"
"out vec4 color;\n"

"in vec3 Texcoords;\n"

"uniform samplerCube Texture;\n"

"void main(){\n"
"color = texture(Texture,Texcoords); \n"
"}"
;

static const char* vertexshadersource2 =
"#version 440 core\n"
"layout(location = 0) in vec2 vertexPosition_modelspace;\n"
"layout(location = 1) in vec2 texCoords;\n"
"out vec2 Texcoords;\n"
"uniform mat4 projection;\n"
"uniform mat4 view;\n"
"uniform mat4 model;\n"

"void main(){\n"
"gl_Position=projection * view * model *vec4(vertexPosition_modelspace,0.0,1.0);\n"
"Texcoords=texCoords;\n"
"}"
;

static const char* fragshadersource2 =
"#version 440 core\n"
"uniform sampler2D Texture;\n"
"uniform vec4 twopos;\n"
"in vec2 Texcoords;\n"
"out vec4 color;\n"
"void main(){\n"
"color=vec4(1,1,1,1);\n"
"}"
;


static map<int, bool >keystatus;
static GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
static GLfloat lastFrame = 0.0f;  	// Time of last frame
static vec3 cameraPos = vec3(0.0f, 0.0f, .0f);
static vec3 cameraFront = vec3(0.0f, 0.0f, -1.0f);
static vec3 cameraUp = vec3(0.0f, 1.0f, 0.0f);
static bool firstMouse = true;
static GLfloat lastX, lastY, xpose, ypos;

void do_movement()
{
	// Camera controls
	GLfloat cameraSpeed = 5.0f * deltaTime;
	if (keystatus[GLFW_KEY_W])
		cameraPos += cameraSpeed * cameraFront;
	else if (keystatus[GLFW_KEY_S])
		cameraPos -= cameraSpeed * cameraFront;
	else if (keystatus[GLFW_KEY_A])
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	//cameraPos -= vec3(1, 0, 0)*cameraSpeed;
	else if (keystatus[GLFW_KEY_D])
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	//cameraPos += vec3(1, 0, 0)*cameraSpeed;
	else if (keystatus[GLFW_KEY_U])
		cameraPos += normalize(cameraUp)*cameraSpeed;
	else if (keystatus[GLFW_KEY_J])
		cameraPos -= normalize(cameraUp)*cameraSpeed;
}
static GLfloat speed=3.f;
static GLfloat yaw, pitch;
void changefront(GLfloat x,GLfloat y){
	cameraFront += speed*vec3(sin(radians(x)), 0, -cos(radians(x)));
	cameraFront = normalize(cameraFront);
	//cameraUp = vec3(0, cos(radians(y)), 0);
};

GLuint loadTexture(char* path);
int _tmain(int argc, _TCHAR* argv[])
{
	glfwInit();
	auto window = glfwCreateWindow(800, 600, "frambuffer", NULL, NULL);
	glfwMakeContextCurrent(window);
	glewInit();
	glfwSetErrorCallback(
		[](int error, const char * desc){
		fprintf_s(stderr, "ERROR:%s\n", desc);
	}
	);

	GLuint skybox = SOIL_load_OGL_cubemap(
		"E:/hit/frambuffertest/frambuffertest/mp_orbital/orbital-element_ft.tga",
		"E:/hit/frambuffertest/frambuffertest/mp_orbital/orbital-element_bk.tga",
		"E:/hit/frambuffertest/frambuffertest/mp_orbital/orbital-element_up.tga",
		"E:/hit/frambuffertest/frambuffertest/mp_orbital/orbital-element_dn.tga",
		"E:/hit/frambuffertest/frambuffertest/mp_orbital/orbital-element_rt.tga",
		"E:/hit/frambuffertest/frambuffertest/mp_orbital/orbital-element_lf.tga",
		SOIL_LOAD_RGB,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS
		);

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);



	GLuint sb_vao, sb_vbo;
	glGenVertexArrays(1, &sb_vao);
	glGenBuffers(1, &sb_vbo);
	glBindVertexArray(sb_vao);
	glBindBuffer(GL_ARRAY_BUFFER, sb_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	GL glsb;
	glsb.creatProgram(const_cast<char*>(vertexshadersource1), const_cast<char*>(fragshadersource1));
	//glProgramUniformMatrix4fv(glsb.shaderprogram, glGetUniformLocation(glsb.shaderprogram, "model"))

	GLuint f1_vao, f1_vbo;
	glGenVertexArrays(1, &f1_vao);
	glGenBuffers(1, &f1_vbo);
	glBindVertexArray(f1_vao);
	glBindBuffer(GL_ARRAY_BUFFER, f1_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);

	GLuint quadVAO, quadVBO;
	glGenVertexArrays(1, &quadVAO);
	glGenBuffers(1, &quadVBO);
	glBindVertexArray(quadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
	glBindVertexArray(0);

	GLuint fbo, rbo, tex;
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	//glNamedFramebufferTexture(fbo, GL_COLOR_ATTACHMENT0, tex, 0);
	glFramebufferTextureEXT(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, tex, 0);

	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 600);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//new
	GLuint fbo1, tex1;
	glGenFramebuffers(1, &fbo1);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo1);
	glGenTextures(1, &tex1);
	glBindTexture(GL_TEXTURE_2D, tex1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 20, 10, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	//glNamedFramebufferTexture
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, tex1, 0);
	/*glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);*/
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	GLfloat point[] = { 0, 0, 0, 2, 1, 0 };
	GLuint vaop, vbop;
	glGenVertexArrays(1, &vaop);
	glGenBuffers(1, &vbop);
	glBindVertexArray(vaop);
	glBindBuffer(GL_ARRAY_BUFFER, vbop);
	glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	keystatus[GLFW_KEY_W] = false;
	keystatus[GLFW_KEY_A] = false;
	keystatus[GLFW_KEY_S] = false;
	keystatus[GLFW_KEY_D] = false;
	keystatus[GLFW_KEY_U] = false;
	keystatus[GLFW_KEY_J] = false;
	glfwSetKeyCallback(
		window,
		[](GLFWwindow* win, int key, int scancode, int action, int mods){
		switch (key){
		case GLFW_KEY_W:
		case GLFW_KEY_A:
		case GLFW_KEY_S:
		case GLFW_KEY_D:
		case GLFW_KEY_U:
		case GLFW_KEY_J:
			if (action == GLFW_PRESS)
				keystatus[key] = true;
			if (action == GLFW_RELEASE)
				keystatus[key] = false;
			break;

		case GLFW_KEY_R:
			cameraPos = vec3(0, 0, 7);
			break;

		default:
			break;

		}
	});

	glfwSetCursorPosCallback(window,
		[](GLFWwindow* window, double xpos, double ypos){
		if (firstMouse)
		{
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}

		GLfloat xoffset = xpos - lastX;
		GLfloat yoffset = lastY - ypos;
		char str[200];
		sprintf_s(str, 200, "%f", xoffset);
		/*sprintf_s(str,sizeof(yoffset), "%f", yoffset);
		strcat_s(str, sizeof(str), str2);*/
		glfwSetWindowTitle(window, str);
		GLfloat sensitivity = 0.15;
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		yaw += xoffset;
		pitch += yoffset;

		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;

		glm::vec3 front;
		front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		front.y = sin(glm::radians(pitch));
		front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		cameraFront = glm::normalize(front);
		lastX = xpos;
		lastY = ypos;
	}
	);

	GLuint f1_tex = loadTexture("E:\\tf.jpg");

	GL gl,glo,gldp;
	gl.creatProgram(const_cast<char*>(vertexshadersource0), const_cast<char*>(fragshadersource0));
	glo.creatProgram(const_cast<char*>(vertexshadersource0), const_cast<char*>(fragshadersource0));
	gldp.creatProgram(const_cast<char*>(vertexshadersource2), const_cast<char*>(fragshadersource2));
	
	GLubyte* pixels = (GLubyte*)malloc(512);

	GLuint shaderprogram = gl.shaderprogram,shaderprogram2=glo.shaderprogram;
	//glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

	float lasttime = 0.f;

	char buffer[50];
	sprintf_s(buffer, 9, "%f", 1.1f);
	sprintf_s(buffer, 10, "%s", "end");
	cout << buffer << endl;
	srand(glfwGetTime());
	cout << rand() % 50 << endl;

	//system("pause");
	mat4 view1 = lookAtRH(vec3(0, 0, 3), vec3(0, 0, 0), vec3(0, 1, 0));

		glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window)){
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		do_movement();
		mat4 projection = perspective(radians(70.f), 4.f / 3.f, 0.1f, 300.f);
		mat4 view = lookAtRH(cameraPos, cameraPos + cameraFront, cameraUp);
		float now = glfwGetTime();
		mat4 model = rotate(5 * radians(now), vec3(0, 1, 0));
		mat4 transform = mat4(1);
		model = mat4(1);

		//cube frambuffer
		glViewport(0, 0, 800, 600);
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		glClearColor(1, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(gl.shaderprogram);
		glUniformMatrix4fv(glGetUniformLocation(shaderprogram, "projection"), 1, GL_FALSE, (float*)&projection);
		glUniformMatrix4fv(glGetUniformLocation(shaderprogram, "view"), 1, GL_FALSE, (float*)&mat4(mat3(view)));
		glUniformMatrix4fv(glGetUniformLocation(shaderprogram, "model"), 1, GL_FALSE, (float*)&model);
		glBindVertexArray(f1_vao);
		glBindTexture(GL_TEXTURE_2D, f1_tex);
		glActiveTexture(GL_TEXTURE0);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindVertexArray(0);
		glBindFramebuffer(GL_FRAMEBUFFER,0);
		glUseProgram(0);
				
		glClearColor(1.0f, 1.0f, .0f, 1.0f); // Set clear color to white (not really necessery actually, since we won't be able to see behind the quad anyways)
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//framebuffer number 2
		glViewport(0, 0, 20, 10);
		glBindFramebuffer(GL_FRAMEBUFFER, fbo1);
		/*glUseProgram(gldp.shaderprogram);
		glUniform4f(glGetUniformLocation(gldp.shaderprogram, "twopos"), 0.2, 0.2, 0.4, 0.4);
		glUniformMatrix4fv(glGetUniformLocation(gldp.shaderprogram, "projection"), 1, GL_FALSE, (float*)&projection);
		glUniformMatrix4fv(glGetUniformLocation(gldp.shaderprogram, "view"), 1, GL_FALSE, (float*)&mat4(mat3(view1)));
		glUniformMatrix4fv(glGetUniformLocation(gldp.shaderprogram, "model"), 1, GL_FALSE, (float*)&model);*/
		/*glUseProgram(gl.shaderprogram);
		glUniformMatrix4fv(glGetUniformLocation(shaderprogram, "projection"), 1, GL_FALSE, (float*)&projection);
		glUniformMatrix4fv(glGetUniformLocation(shaderprogram, "view"), 1, GL_FALSE, (float*)&mat4(mat3(view)));
		glUniformMatrix4fv(glGetUniformLocation(shaderprogram, "model"), 1, GL_FALSE, (float*)&model);

		glBindTexture(GL_TEXTURE_2D, f1_tex);
		glBindVertexArray(quadVAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);*/
		glUseProgram(shaderprogram2);
		/*glUniformMatrix4fv(glGetUniformLocation(shaderprogram2, "model"), 1, GL_FALSE, (float*)&model);
		glUniformMatrix4fv(glGetUniformLocation(shaderprogram2, "view"), 1, GL_FALSE, (float*)&view1);
		glUniformMatrix4fv(glGetUniformLocation(shaderprogram2, "projection"), 1, GL_FALSE, (float*)&projection);*/
		glBindVertexArray(quadVAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindVertexArray(0);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glUseProgram(0);
		/*glBindTexture(GL_TEXTURE_2D, tex1);
		glGetTexImage(GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
		glBindTexture(GL_TEXTURE_2D, 0);*/

		//display framebuffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, 800, 600);
		glUseProgram(shaderprogram2);
		model = translate(model, vec3(0, 0, -5));
		glUniformMatrix4fv(glGetUniformLocation(shaderprogram2, "model"), 1, GL_FALSE, (float*)&model);
		glUniformMatrix4fv(glGetUniformLocation(shaderprogram2, "view"), 1, GL_FALSE, (float*)&view);
		glUniformMatrix4fv(glGetUniformLocation(shaderprogram2, "projection"), 1, GL_FALSE, (float*)&projection);
		glBindVertexArray(quadVAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex1);	
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindVertexArray(0);
		glUseProgram(0);

		//skybox
		glDepthFunc(GL_LEQUAL);
		glUseProgram(glsb.shaderprogram);
		mat4 sview = mat4(mat3(view));
		glUniformMatrix4fv(glGetUniformLocation(glsb.shaderprogram, "view"), 1, GL_FALSE, (float*)&sview);
		glUniformMatrix4fv(glGetUniformLocation(glsb.shaderprogram, "model"), 1, GL_FALSE, (float*)&model);
		glUniformMatrix4fv(glGetUniformLocation(glsb.shaderprogram, "projection"), 1, GL_FALSE, (float*)&projection);
		glBindVertexArray(sb_vao);
		glActiveTexture(GL_TEXTURE0);
		//glUniform1i(glGetUniformLocation(glsb.shaderprogram, "texSkyBox"), 0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, skybox);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		glBindVertexArray(0);
		glUseProgram(0);
		glDepthFunc(GL_LESS);


		

		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	return 0;
}

GLuint loadTexture(char* path){
	GLuint texID;
	GLint width, height;
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);
	GLubyte* image = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(image);
	return texID;
}
