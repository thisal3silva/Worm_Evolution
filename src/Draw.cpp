

#define len 10

void drawWorm(double x, double y, double angle)
{
	glLineWidth(2);
	glColor3f(1, 0, 0);
	float wOffset = sin(angle) * len / 2.0;
	float hOffset = cos(angle) * len / 2.0;
	glBegin(GL_LINE_LOOP);
	glVertex2f(x - wOffset, y  + hOffset);
	glVertex2f(x + wOffset, y  - hOffset);
	glEnd();
}
