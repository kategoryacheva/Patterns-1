#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>

class Exception 
{
	public:
		virtual std::string what() const = 0;
};

class ExInitFailed : public Exception 
{
	private:
		std::string m_error;
	public:
		ExInitFailed(const std::string& error) : m_error(error) {}
		std::string what() const 
		{
			return "Error: Failed to init SDL: " + m_error;
		}
};

class ExWindowCreationFailed : public Exception 
{
	private:
		std::string m_error;
	public:
		ExWindowCreationFailed(const std::string& error) : m_error(error) {}
		std::string what() const 
		{
			return "Error: Failed to create window: " + m_error;
		}
};

class ExRendererCreationFailed : public Exception 
{
	private:
		std::string m_error;
	public:
		ExRendererCreationFailed(const std::string& error) : m_error(error) {}
		std::string what() const 
		{
			return "Error: Failed to create renderer: " + m_error;
		}
};

class ExInvalidUnit : public Exception 
{
	private:
		std::string m_error;
	public:
		ExInvalidUnit(const std::string& error) : m_error(error) {}
		std::string what() const 
		{
			return "Error: Invalid unit: " + m_error;
		}
};
#endif
