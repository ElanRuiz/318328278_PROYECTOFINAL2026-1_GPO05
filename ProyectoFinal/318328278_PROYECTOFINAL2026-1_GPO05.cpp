// Ruiz Aguilar Cristian Jair
// 318328278
// GPO 05

#include <iostream>
#include <cmath>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other Libs
#include "stb_image.h"

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Load Models
#include "SOIL2/SOIL2.h"


// Other includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include "Texture.h"

// Function prototypes
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void DoMovement();

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Camera
Camera  camera(glm::vec3(0.0f, 0.0f, 3.0f));

GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];
bool firstMouse = true;
// Light attributes
glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
bool active;

// ========= SIMPLE ANIMATIONS ============

// CORTINA1 ANIMATION
bool Cortina_abierta1 = true; // Indica si la cortina esta abierta
bool anima_cortina1 = false; // Indica si la animacion esta en curso
float cortinaAbre1 = 1.0f; // cantidad de escalamiento (apertura) de la cortina

// CORTINA2 ANIMATION
bool Cortina_abierta2 = true; // Indica si la cortina esta abierta
bool anima_cortina2 = false; // Indica si la animacion esta en curso
float cortinaAbre2 = 1.0f; // cantidad de escalamiento (apertura) de la cortina

// REJA ANIMATION
bool rejaAbierta = false; // Indica si la reja esta abierta
bool anima_reja = false; // Indica si la animacion esta en curso
float rejaAbre = 46.297f; // cantidad de rotacion (apertura) de la reja

// PUERTA ENTRADA ANIMATION
bool puertaEntradaAbierta = false; // Indica si la puerta de entrada esta abierta
bool anima_puertaEntrada = false; // Indica si la animacion esta en curso
float puertaEntradaAbre = 0.0f; // cantidad de rotacion (apertura) de la puerta de entrada

// PUERTA COMEDOR ANIMATION
bool puertaComedorAbierta = false; // Indica si la puerta de entrada esta abierta
bool anima_puertaComedor = false; // Indica si la animacion esta en curso
float puertaComedorAbre = 0.0f; // cantidad de rotacion (apertura) de la puerta de entrada

// PUERTA RECAMARA ANIMATION
bool puertaRecamaraAbierta = false; // Indica si la puerta de la recamara esta abierta
bool anima_puertaRecamara = false; // Indica si la animacion esta en curso
float puertaRecamaraAbre = 0.0f; // cantidad de rotacion (apertura) de la puerta de la recamara

// CAJON ANIMATION
bool cajonAbierta = false; // Indica si el cajon esta salido
bool anima_cajon = false; // Indica si la animacion esta en curso
float cajonAbre = -10.159; // cantidad de distancia recorrida (apertura) del cajon


// ============ COMPLEX ANIMATINOS =============

float tiempo; // Anim_Arbol

// MARIPOSA ANIMATION
bool alaSubida = true; // Indica si la puerta de entrada esta abierta
bool anima_ala = false; // Indica si la animacion esta en curso
float aleteoAbre = 0.0f; // cantidad de rotacion (apertura) de la puerta de entrada

float alaRot = 0.0f;        // rotación del ala (de -75.0f a 75.0f)
float velocidadAleteo = 300.0f;  // Velocidad
bool alaSubiendo = true;         // Direccion actual del aleteo
const float limiteRotacion = 75.0f; // maximo angulo de rotacion



// Positions of the point lights
glm::vec3 pointLightPositions[] = {
	glm::vec3(0.0f,0.0f, 0.0f),
	glm::vec3(0.0f,0.0f, 0.0f),
	glm::vec3(0.0f,0.0f,  0.0f),
	glm::vec3(0.0f,0.0f, 0.0f)
};

glm::vec3 LightP1;

GLfloat skyboxVertices[] = {
	// Positions
	-1.0f,  1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	-1.0f,  1.0f, -1.0f,
	1.0f,  1.0f, -1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	1.0f, -1.0f,  1.0f
};

glm::vec3 Light1 = glm::vec3(0);
glm::vec3 Light2 = glm::vec3(0);
glm::vec3 Light3 = glm::vec3(0);
glm::vec3 Light4 = glm::vec3(0);



// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame

// Posicion y direccion de spotlight
glm::vec3 spotLightPos(0.0f, 0.0f, 0.0f);
glm::vec3 spotLightDir(0.0f, 1.0f, 0.0f); // Apunta hacia abajo por defecto

int main()
{
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Casa de Bety", nullptr, nullptr);

	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

	// Set the required callback functions
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetCursorPosCallback(window, MouseCallback);

	// GLFW Options
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Define the viewport dimensions
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);


	// SHADERS

	Shader lightingShader("Shaders/lighting.vs", "Shaders/lighting.frag");
	Shader lampShader("Shaders/lamp.vs", "Shaders/lamp.frag");
	Shader SkyBoxshader("Shaders/SkyBox.vs", "Shaders/SkyBox.frag");
	Shader Anim_arbol("Shaders/anim.vs", "Shaders/anim.frag");
	Shader Anim_mariposa("Shaders/Anim2.vs", "Shaders/Anim2.frag");

	// OBJECTS IN COMEDOR

	Model CasaBety((char*)"Models/CasaBety/Casa_de_Bety.obj");
	Model Platos((char*)"Models/Comedor/Platos.obj");
	Model BaseMesa((char*)"Models/Comedor/Mesa.obj");
	Model Sillas((char*)"Models/Comedor/Sillas.obj");
	Model Vasijas((char*)"Models/Comedor/Vasijas.obj");
	Model Cuadros((char*)"Models/Comedor/Cuadros.obj");
	Model Muebles((char*)"Models/Comedor/Muebles.obj");

	// OBJECTS IN CUARTO DE BETTY

	Model Cama((char*)"Models/Cuarto_Betty/Cama.obj");                       // #1
	Model Buros((char*)"Models/Cuarto_Betty/Buros.obj");                    // #2
	Model Escritorio((char*)"Models/Cuarto_Betty/Escritorio.obj");     // #3
	Model Computadora((char*)"Models/Cuarto_Betty/Computadora.obj");  // #4
	Model Armario((char*)"Models/Cuarto_Betty/Armario.obj");              // #5
	Model Objetos_Extra((char*)"Models/Cuarto_Betty/Objetos_Extra.obj");
	Model Cortina_Esfera((char*)"Models/Cuarto_Betty/Cortina_y_esfera.obj");

	// OBJECTS WITH SOME TRANSPARENCY

	Model MantelMesa((char*)"Models/Comedor/Mantel_mesa.obj");
	Model Vasos((char*)"Models/Comedor/Vasos.obj");
	Model Vidrios((char*)"Models/Comedor/Vidrios.obj");
	

	// SIMPLE ANIMATION OBJECTS

	Model Reja_entrada((char*)"Models/Animaciones_sencillas/Reja_entrada.obj");
	Model Cortina1((char*)"Models/Comedor/Cortina1.obj");
	Model Cortina2((char*)"Models/Comedor/Cortina2.obj");
	Model PuertaEntrada((char*)"Models/Animaciones_sencillas/Puerta_entrada.obj");
	Model PuertaComedor((char*)"Models/Animaciones_sencillas/Puerta_comedor.obj");
	Model Cajon((char*)"Models/Animaciones_sencillas/Cajon_Comedor.obj");
	Model PuertaRecamara((char*)"Models/Animaciones_sencillas/Puerta_recamara.obj");

	// COMPLEX ANIMATION OBJECTS

	Model HojasArboles((char*)"Models/Animaciones_complejas/Hojas_arbol.obj");
	Model Mariposa_cuerpo((char*)"Models/Animaciones_complejas/Cuerpo_mariposa.obj");
	Model Mariposa_alaDerecha((char*)"Models/Animaciones_complejas/Ala_derecha.obj");
	Model Mariposa_alaIzquierda((char*)"Models/Animaciones_complejas/Ala_izquierda.obj");


	// First, set the container's VAO (and VBO)
	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Set texture units
	lightingShader.Use();

	//SkyBox
	GLuint skyboxVBO, skyboxVAO;
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

	// Load textures
	vector<const GLchar*> faces;
	faces.push_back("SkyBox/right.tga");
	faces.push_back("SkyBox/left.tga");
	faces.push_back("SkyBox/top.tga");
	faces.push_back("SkyBox/bottom.tga");
	faces.push_back("SkyBox/back.tga");
	faces.push_back("SkyBox/front.tga");

	GLuint cubemapTexture = TextureLoading::LoadCubemap(faces);

	glm::mat4 projection = glm::perspective(camera.GetZoom(), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 1000.0f);

	// Game loop
	while (!glfwWindowShouldClose(window))
	{

		// Calculate deltatime of current frame
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		DoMovement();

		// Clear the colorbuffer
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// OpenGL options
		glEnable(GL_DEPTH_TEST);



		//Load Model


		// Use cooresponding shader when setting uniforms/drawing objects
		lightingShader.Use();

		glUniform1i(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 0);
		glUniform1i(glGetUniformLocation(lightingShader.Program, "specular"), 1);

		GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
		glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);


		// Directional light
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.ambient"), 0.668f, 0.649f, 0.582f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.diffuse"), 0.668f, 0.649f, 0.582f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.specular"), 0.5f, 0.5f, 0.5f);

		// Point light 1
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].ambient"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].diffuse"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].specular"), 0.0f, 0.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].quadratic"), 0.032f);

		// Point light 2
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].position"), pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].ambient"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].diffuse"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].specular"), 0.0f, 0.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].quadratic"), 0.032f);

		// Point light 3
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].position"), pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].ambient"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].diffuse"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].specular"), 0.0f, 0.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].quadratic"), 0.032f);

		// Point light 4
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].position"), pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].ambient"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].diffuse"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].specular"), 0.0f, 0.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].quadratic"), 0.032f);

		// SpotLight
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.position"), camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.direction"), camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.ambient"), 0.0f,0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.diffuse"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.specular"), 0.0f, 0.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.linear"), 0.045f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.quadratic"), 0.0075f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.cutOff"), glm::cos(glm::radians(12.0f)));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.outerCutOff"), glm::cos(glm::radians(15.0f)));

		// Set material properties
		glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 16.0f);

		// Create camera transformations
		glm::mat4 view;
		view = camera.GetViewMatrix();

		// Get the uniform locations
		GLint modelLoc = glGetUniformLocation(lightingShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(lightingShader.Program, "view");
		GLint projLoc = glGetUniformLocation(lightingShader.Program, "projection");

		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		glm::mat4 model(1);
		view = camera.GetViewMatrix();
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTrans"), 1);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "tras"), 1.0, 1.0, 1.0, 1.0);
		

		// ====== LOAD HOUSE ======

		// CASA DE BETY
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		CasaBety.Draw(lightingShader);

		// ====== LOAD OBJECTS ======
		
		// BASE MESA DEL COMEDOR
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		BaseMesa.Draw(lightingShader);

		// SILLAS
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Sillas.Draw(lightingShader);

		// PLATOS
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Platos.Draw(lightingShader);

		// VASIJAS
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Vasijas.Draw(lightingShader);

		// CUADROS

		
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Cuadros.Draw(lightingShader);

		// MUEBLES
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Muebles.Draw(lightingShader);

		// ========= CUARTO DE BETTY OBJECTS ==========
		
		// CAMA
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Cama.Draw(lightingShader);

		// BUROS
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Buros.Draw(lightingShader);

		// ESCRITORIO
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Escritorio.Draw(lightingShader);

		// COMPUTADORA
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Computadora.Draw(lightingShader);

		// ARMARIO
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Armario.Draw(lightingShader);

		// OBJETOS EXTRA
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Objetos_Extra.Draw(lightingShader);


		
		// ======== SIMPLE ANIMATION OBJECTS ===========

		// REJA ENTRADA 
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-2.604f, 0.975f, -3.785f));
		model = glm::rotate(model, glm::radians(rejaAbre), glm::vec3(0.0f, 1.0f, 0.0f));
		
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Reja_entrada.Draw(lightingShader);

		// PUERTA ENTRADA
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-11.972f, 1.027f, -6.617f));
		model = glm::rotate(model, glm::radians(puertaEntradaAbre), glm::vec3(0.0f, 1.0f, 0.0f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		PuertaEntrada.Draw(lightingShader);

		// PUERTA COMEDOR
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-10.771f, 0.871f, -7.084f));
		model = glm::rotate(model, glm::radians(puertaComedorAbre), glm::vec3(0.0f, 1.0f, 0.0f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		PuertaComedor.Draw(lightingShader);

		// CAJON
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(cajonAbre, 0.535f, -9.583f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Cajon.Draw(lightingShader);

		// PUERTA RECAMARA
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-6.566f, 5.152f, -13.596f));
		model = glm::rotate(model, glm::radians(-puertaRecamaraAbre), glm::vec3(0.0f, 1.0f, 0.0f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		PuertaRecamara.Draw(lightingShader);


		


		// ====== OBJECTS WITH SOME TRANSPARENCY ======

		glEnable(GL_BLEND);//Avtiva la funcionalidad para trabajar el canal alfa
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		

		// MANTEL MESA COMEDOR
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		
		MantelMesa.Draw(lightingShader);

		// VASOS
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Vasos.Draw(lightingShader);

		// VIDRIOS
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Vidrios.Draw(lightingShader);

		glUniform4f(glGetUniformLocation(lightingShader.Program, "tras"), 1.0, 1.0, 1.0, 0.8);

		// CORTINA Y ESFERA
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Cortina_Esfera.Draw(lightingShader);
		
		glUniform4f(glGetUniformLocation(lightingShader.Program, "tras"), 1.0, 1.0, 1.0, 1.0);

		// ====== ANIMATED OBJECTS WITH SOME TRANSPARENCY ======

		//CORTINA1
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-5.502f, 1.717f, -6.715f)); 
		model = glm::scale(model, glm::vec3(cortinaAbre1, 1.0f, 1.0f)); // cortinaAbre in Animation
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTrans"), 0);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "tras"), 1.0, 1.0, 1.0, 0.9); // agrega traslucides.
		Cortina1.Draw(lightingShader);
		
		//CORTINA2
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-5.551f, 1.72f, -6.675f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, cortinaAbre2)); // cortinaAbre in Animation
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Cortina2.Draw(lightingShader);


		
		
		
		glDisable(GL_BLEND); //Desactiva el canal alfa 

		// ======= COMPLEX ANIMATION OBJECTS =========

		// HOJAS DE ARBOL
		Anim_arbol.Use();
		tiempo = glfwGetTime() * 0.2;

		// Get location objects for the matrices on the lamp shader (these could be different on a different shader)
		modelLoc = glGetUniformLocation(Anim_arbol.Program, "model");
		viewLoc = glGetUniformLocation(Anim_arbol.Program, "view");
		projLoc = glGetUniformLocation(Anim_arbol.Program, "projection");

		// Set matrices
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(Anim_arbol.Program, "time"), tiempo);
		HojasArboles.Draw(Anim_arbol);


		glBindVertexArray(0);
		
		//MARIPOSA
		Anim_mariposa.Use();
		tiempo = glfwGetTime();

		// Get location objects for the matrices on the lamp shader (these could be different on a different shader)
		modelLoc = glGetUniformLocation(Anim_mariposa.Program, "model");
		viewLoc = glGetUniformLocation(Anim_mariposa.Program, "view");
		projLoc = glGetUniformLocation(Anim_mariposa.Program, "projection");

		// Set matrices
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-9.107f, 0.469f, -3.094f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(Anim_mariposa.Program, "time"), tiempo);
		Mariposa_cuerpo.Draw(Anim_mariposa);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-9.107f, 0.469f, -3.094f));
		model = glm::rotate(model, glm::radians(aleteoAbre), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(Anim_mariposa.Program, "time"), tiempo);
		Mariposa_alaIzquierda.Draw(Anim_mariposa);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-9.107f, 0.469f, -3.094f));
		model = glm::rotate(model, glm::radians(-aleteoAbre), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(Anim_mariposa.Program, "time"), tiempo);
		Mariposa_alaDerecha.Draw(Anim_mariposa);

		glBindVertexArray(0);



		// Also draw the lamp object, again binding the appropriate shader
		lampShader.Use();
		// Get location objects for the matrices on the lamp shader (these could be different on a different shader)
		modelLoc = glGetUniformLocation(lampShader.Program, "model");
		viewLoc = glGetUniformLocation(lampShader.Program, "view");
		projLoc = glGetUniformLocation(lampShader.Program, "projection");

		// Set matrices
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		model = glm::mat4(1);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		// Draw the light object (using light's vertex attributes)
		for (GLuint i = 0; i < 4; i++)
		{
			model = glm::mat4(1);
			model = glm::translate(model, pointLightPositions[i]);
			model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		glBindVertexArray(0);


		// SHADER PARA RENDERIZAR EL SKYBOX

		// Draw skybox as last
		glDepthFunc(GL_LEQUAL);  // Change depth function so depth test passes when values are equal to depth buffer's content
		SkyBoxshader.Use();
		view = glm::mat4(glm::mat3(camera.GetViewMatrix()));	// Remove any translation component of the view matrix
		glUniformMatrix4fv(glGetUniformLocation(SkyBoxshader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(SkyBoxshader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		// skybox cube
		glBindVertexArray(skyboxVAO);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glDepthFunc(GL_LESS); // Set depth function back to default



		// Swap the screen buffers
		glfwSwapBuffers(window);
	}


	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();



	return 0;
}

// Moves/alters the camera positions based on user input
void DoMovement()
{

	// Camera controls
	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
	{
		camera.ProcessKeyboard(FORWARD, deltaTime);

	}

	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
	{
		camera.ProcessKeyboard(BACKWARD, deltaTime);


	}

	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
	{
		camera.ProcessKeyboard(LEFT, deltaTime);


	}

	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
	{
		camera.ProcessKeyboard(RIGHT, deltaTime);


	}

	//ANIMATION CORTINA1
	if (anima_cortina1) {

		if (!Cortina_abierta1) { // Si esta cerrada

			if (cortinaAbre1 < 1.0f) { // Abre
				cortinaAbre1 += 0.05f;
			}
			else {
				Cortina_abierta1 = true; // ya esta abierta
				anima_cortina1 = false;
			}
		}
		else { // Si esta abierta
			
			if (cortinaAbre1 > 0.225f) {
				cortinaAbre1 -= 0.05f;
			}
			else {
				Cortina_abierta1 = false; // ya esta cerrada
				anima_cortina1 = false;
			}
		}
	}

	//ANIMATION CORTINA2
	if (anima_cortina2) {

		if (!Cortina_abierta2) { // Si esta cerrada

			if (cortinaAbre2 < 1.0f) { // Abre
				cortinaAbre2 += 0.05f;
			}
			else {
				Cortina_abierta2 = true; // ya esta abierta
				anima_cortina2 = false;
			}
		}
		else { // Si esta abierta

			if (cortinaAbre2 > 0.225f) {
				cortinaAbre2 -= 0.05f;
			}
			else {
				Cortina_abierta2 = false; // ya esta cerrada
				anima_cortina2 = false;
			}
		}
	}

	//ANIMATION REJA
	if (anima_reja) {

		if (!rejaAbierta) { // Si esta cerrada

			if (rejaAbre > -29.236f) { // Abre
				rejaAbre -= 2.5f;
			}
			else {
				rejaAbierta = true; // ya esta abierta
				anima_reja = false;
			}
		}
		else { // Si esta abierta

			if (rejaAbre < 46.297f) {
				rejaAbre += 2.5f;
			}
			else {
				rejaAbierta = false; // ya esta cerrada
				anima_reja = false;
			}
		}
	}


	//ANIMATION PUERTA DE ENTRADA
	if (anima_puertaEntrada) {

		if (!puertaEntradaAbierta) { // Si esta cerrada

			if (puertaEntradaAbre > -100.0f) { // Abre
				puertaEntradaAbre -= 2.5f;
			}
			else {
				puertaEntradaAbierta = true; // ya esta abierta
				anima_puertaEntrada = false;
			}
		}
		else { // Si esta abierta

			if (puertaEntradaAbre < 0.0f) {
				puertaEntradaAbre += 2.5f;
			}
			else {
				puertaEntradaAbierta = false; // ya esta cerrada
				anima_puertaEntrada = false;
			}
		}
	}


	//ANIMATION PUERTA DEL COMEDOR
	if (anima_puertaComedor) {

		if (!puertaComedorAbierta) { // Si esta cerrada

			if (puertaComedorAbre > -80.0f) { // Abre
				puertaComedorAbre -= 2.5f;
			}
			else {
				puertaComedorAbierta = true; // ya esta abierta
				anima_puertaComedor = false;
			}
		}
		else { // Si esta abierta

			if (puertaComedorAbre < 0.0f) {
				puertaComedorAbre += 2.5f;
			}
			else {
				puertaComedorAbierta = false; // ya esta cerrada
				anima_puertaComedor = false;
			}
		}
	}


	//ANIMATION PUERTA RECAMARA DE BETTY
	if (anima_puertaRecamara) {

		if (!puertaRecamaraAbierta) { // Si esta cerrada

			if (puertaRecamaraAbre > -90.0f) { // Abre
				puertaRecamaraAbre -= 2.5f;
			}
			else {
				puertaRecamaraAbierta = true; // ya esta abierta
				anima_puertaRecamara = false;
			}
		}
		else { // Si esta abierta

			if (puertaRecamaraAbre < 0.0f) {
				puertaRecamaraAbre += 2.5f;
			}
			else {
				puertaRecamaraAbierta = false; // ya esta cerrada
				anima_puertaRecamara = false;
			}
		}
	}


	//ANIMATION CAJON
	if (anima_cajon) {

		if (!cajonAbierta) { // Si esta cerrado

			if (cajonAbre < -9.9f) { // Abre
				cajonAbre += 0.02f;
			}
			else {
				cajonAbierta = true; // ya esta abierto
				anima_cajon = false;
			}
		}
		else { // Si esta abierto

			if (cajonAbre > -10.159) {
				cajonAbre -= 0.02f;
			}
			else {
				cajonAbierta = false; // ya esta cerrado
				anima_cajon = false;
			}
		}
	}

	//ANIMATION MARIPOSA - ALETEO CONSTANTE
	if (alaSubiendo) {
		aleteoAbre += 25.0f;
		if (aleteoAbre >= limiteRotacion)
			alaSubiendo = false;
	}
	else {
		aleteoAbre -= 25.0f;
		if (aleteoAbre <= -limiteRotacion)
			alaSubiendo = true;
	}

	



}







// Is called whenever a key is pressed/released via GLFW
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			keys[key] = false;
		}
	}

	if (keys[GLFW_KEY_1] && !anima_cortina1) { // ANIMATION CORTINA1
		anima_cortina1 = true;
	}

	if (keys[GLFW_KEY_2] && !anima_cortina2) { // ANIMATION CORTINA2
		anima_cortina2 = true;
	}

	if (keys[GLFW_KEY_3] && !anima_reja) { // ANIMATION REJA
		anima_reja = true;
	}

	if (keys[GLFW_KEY_4] && !anima_puertaEntrada) { // ANIMATION PUERTA ENTRADA
		anima_puertaEntrada = true;
	}

	if (keys[GLFW_KEY_5] && !anima_puertaComedor) { // ANIMATION PUERTA COMEDOR
		anima_puertaComedor = true;
	}

	if (keys[GLFW_KEY_6] && !anima_cajon) { // ANIMATION CAJON
		anima_cajon = true;
	}

	if (keys[GLFW_KEY_7] && !anima_puertaRecamara) { // ANIMATION PUERTA RECAMARA
		anima_puertaRecamara = true;
	}

}

void MouseCallback(GLFWwindow* window, double xPos, double yPos)
{
	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	GLfloat xOffset = xPos - lastX;
	GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left

	lastX = xPos;
	lastY = yPos;

	camera.ProcessMouseMovement(xOffset, yOffset);
}