#include <GL/freeglut.h>

class Obserwator {
public:
	Obserwator();
	~Obserwator() = default;

private:
	static const GLfloat position[3];
	static const GLfloat normal[3];

};