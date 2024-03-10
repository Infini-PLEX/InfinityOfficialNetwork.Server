#pragma once

#include <string>
#include <vector>

namespace InfinityOfficialNetwork::Core::JavaWrapper::JDK21
{
	class JavaVMWrapper {
	public:
		JavaVMWrapper(const std::string& classpath, const std::string& mainClassName);
		~JavaVMWrapper();
		void Launch(const std::vector<std::string>& args);

	private:
		class JavaVMWrapperImpl;
		JavaVMWrapperImpl* impl;
	};

	class JavaVMException : public std::exception {
	private:
		const std::string message;

	public:
		const enum class Type {
			CREATE_JVM,
			FIND_MAIN_CLASS,
			FIND_MAIN_METHOD,
			JVM_EXECUTION
		};

	private:
		Type type;

	public:
		inline const JavaVMException(const std::string& msg, Type type) :
			message(msg),
			type(type)
		{}

		inline const char* what()
			const noexcept override
		{
			return message.c_str();
		}

		inline const Type ExceptionType()
			const noexcept
		{
			return type;
		}
	};
}