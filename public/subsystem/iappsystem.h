#pragma once

#define APPSYSTEM_OBJECT(version)	\
	public:	\
		bool Setup() override;	\
		void Shutdown() override;	\
		const char* GetSystemName() const override { return (version); };	\
		bool IsSetup() const override { return m_bIsSetup; };	\
	private:	\
		bool m_bIsSetup;	\


abstract_class IAppSystem
{
public:
	virtual bool Setup() = 0;
	virtual void Shutdown() = 0;
	virtual const char* GetSystemName() const = 0;
	virtual bool IsSetup() const = 0;
};