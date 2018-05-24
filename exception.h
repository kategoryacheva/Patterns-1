#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>

class Exception 
{
	public:
		virtual std::string what() const = 0;
};

class InitFailed : public Exception 
{
	private:
		std::string m_error;
	public:
		InitFailed(const std::string& error) : m_error(error) {}
		std::string what() const 
		{
			return "Error: Failed to init SDL: " + m_error;
		}
};

class WindowCreationFailed : public Exception 
{
	private:
		std::string m_error;
	public:
		WindowCreationFailed(const std::string& error) : m_error(error) {}
		std::string what() const 
		{
			return "Error: Failed to create window: " + m_error;
		}
};

class RendererCreationFailed : public Exception 
{
	private:
		std::string m_error;
	public:
		RendererCreationFailed(const std::string& error) : m_error(error) {}
		std::string what() const 
		{
			return "Error: Failed to create renderer: " + m_error;
		}
};

class InvalidUnit : public Exception 
{
	private:
		std::string m_error;
	public:
		InvalidUnit(const std::string& error) : m_error(error) {}
		std::string what() const 
		{
			return "Error: Invalid unit: " + m_error;
		}
};
#endif
