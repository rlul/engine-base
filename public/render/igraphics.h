#pragm


#pragma once



abstract_class IGraphics
{
public:
	virtual ~IGraphics() = 0;

	virtual bool Initialize() = 0;
	virtual bool Shutdown() = 0;
}
