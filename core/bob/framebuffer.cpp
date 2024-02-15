#include "framebuffer.h"
#include "iostream"
namespace bob {
	Framebuffer createFramebuffer(unsigned int width, unsigned int height, int colorFormat)
	{
		Framebuffer framebuffer;
		glCreateFramebuffers(1, &framebuffer.fbo);

		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer.fbo);
		//Color Buffer
		glGenTextures(1, framebuffer.colorBuffer);
		glBindTexture(GL_TEXTURE_2D, *framebuffer.colorBuffer);
		glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, width, height);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, *framebuffer.colorBuffer, 0);

		//Depth Buffer
		glGenTextures(1, &framebuffer.depthBuffer);
		glBindTexture(GL_TEXTURE_2D, framebuffer.depthBuffer);
		glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH_COMPONENT16, width, height);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, framebuffer.depthBuffer, 0);

		GLenum fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (fboStatus != GL_FRAMEBUFFER_COMPLETE)
		{
			std::cout << "Framebuffer incomplete: %d " << fboStatus;
		}
		return framebuffer;
	}
}