#ifndef __TEXT_H_
#define __TEXT_H_

class Text
{
public:
	Text(const char* text);
	void update();
	void render();
	void setContent(const char* content);
	const char* getContent();
private:
	const char* content;
};

#endif