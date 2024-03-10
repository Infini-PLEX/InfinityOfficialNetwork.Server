#pragma once

#include <string>
#include <vector>

namespace InfinityOfficialNetwork::Server::Core::JavaWrapper::JDK21 {
	class JavaVirtualMachine {
	public:
		JavaVirtualMachine(
			const std::string& jarPath, 
			const std::vector<std::string>& args,
			std::wistream* In,
			std::wostream* Out,
			std::wostream* Err
		);

		~JavaVirtualMachine();

		int InvokeJavaVirtualMachine();

	private:
		std::wistream* JVMIn;
		std::wostream* JVMOut;
		std::wostream* JVMErr;

		class JavaVirtualMachineImpl;
		JavaVirtualMachineImpl* Impl;
	};
}