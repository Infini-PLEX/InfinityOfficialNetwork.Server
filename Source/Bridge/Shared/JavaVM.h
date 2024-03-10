#pragma once

#include "../../Core/JavaInitializer/JavaVM.h"

#include <msclr/marshal.h>
#include <msclr/marshal_cppstd.h>

namespace InfinityOfficialNetwork::Server::Bridge::Shared {
	public ref class JavaVM {
	private:
		InfinityOfficialNetwork::Server::Core::JavaInitializer::JavaVM* Instance;

	public:
		ref class Version {
			InfinityOfficialNetwork::Server::Core::JavaInitializer::JavaVM::Version* Instance;
		} JavaVersion;

		ref class Arguments {
		private:
			InfinityOfficialNetwork::Server::Core::JavaInitializer::JavaVM::Arguments* Instance;

		public:
			property std::size_t MinRam {
				std::size_t get() {
					return Instance->MinRam;
				}
				void set(std::size_t v) {
					Instance->MinRam = v;
				}
			}

			property std::size_t MaxRam {
				std::size_t get() {
					return Instance->MaxRam;
				}
				void set(std::size_t v) {
					Instance->MaxRam = v;
				}
			}

			property System::String^ JarPath {
				System::String^ get() {
					return msclr::interop::marshal_as<System::String^>(Instance->JarPath);
				}
				void set(System::String^ v) {
					Instance->JarPath = msclr::interop::marshal_as<std::string>(v);
				}
			}

			property System::Collections::Generic::List<System::String^>^ AdditionalArguments {
				System::Collections::Generic::List<System::String^>^ get() {
					System::Collections::Generic::List<System::String^>^ List = 
						gcnew System::Collections::Generic::List<System::String^>
						(Instance->AdditionalArguments.size());
					for each (const auto str in Instance->AdditionalArguments) {
						List->Add(msclr::interop::marshal_as<System::String^>(str));
					}
					return List;
				}
				void set(System::Collections::Generic::List<System::String^>^ v) {
					std::vector<std::string> List;
					for each (System::String^ str in v) {
						List.push_back(msclr::interop::marshal_as<std::string>(str));
					}
				}
			}

			property bool NoGui {
				bool get() {
					return Instance->NoGui;
				}
				void set(bool v) {
					Instance->NoGui = v;
				}
			}
		} JavaArguments;

		ref class Streams {

		};
	};
}