#ifndef __LAYER_H_
#define __LAYER_H_

class Layer
{
public:
	bool enabled();
	void setEnabled(bool state);
	const char* getTitle();
	void setTitle(const char* title);
private:
	bool enabled;
	const char* title;
};

#endif