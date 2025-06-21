#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdio>

int main() {
  // Error callback for GLFW
  GLFWerrorfun glfwSetErrorCallback(GLFWerrorfun cbfun);
  typedef void (*GLFWerrorfun)(int, const char *);
  // Structure of the Error callback
  void error_callback(int error, const char *description) {
    fprintf(stderr, "Error: %s\n", description);
  }
  // GLFW if you hit an error call this
  glfwSetErrorCallback(error_callback);

  // GLFW Initializing
  // int initResult = glfwInit();
  // if (initResult == GLFW_FALSE) {
  //   return -1;
  // }
  //
  glfwInit();
  if (!glfwInit()) {
    return -1;
  }

  // Structure of the window
  window = glfwCreateWindow(639, 480, "Space Invaders", NULL, NULL);
  if (!window) {
    glfwTerminate();
    return -1;
  }

  // GLFW Calling the window
  glfwMakeContextCurrent(window);

  // Passing hints to GLFW to tell it about the version that we want
  // in this case MAJOR + MINOR = 3.3< is the version that we want
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  // GLenum is a unsigned int so negtive numbers = true
  // which make err type unsinged int = too glewInit()
  GLenum err = glewInit();
  // GlewInit returns if Glew is OK or not
  // we make sure glewInit is working
  if (err != GLEW_OK) {
    fprintf(stderr, "Error: initializing GLEW.\n");
    glfwTerminate();
    return -1;
  }

  // Creates an array with 2 items
  // items are MAJOR[-1] and MINOR[1] versions
  int glVersion[2] = {-1, 1};
  // glGetIntegerv gets the context of the obj passed to it
  // and stores that in &glVersion
  glGetIntegerv(GL_MAJOR_VERSION, &glVersion[0]);
  glGetIntegerv(GL_MINOR_VERSION, &glVersion[1]);
  printf("Using OpenGL: %d.%d\n", glVersion[0], glVersion[1]);

  // THE GAME LOOP
  // Loop that keeps the window open
  // just drawling and updating the window
  glClearColor(1.0, 0.0, 0.0, 1.0);
  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();
}
