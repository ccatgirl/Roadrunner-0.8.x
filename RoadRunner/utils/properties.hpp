#pragma once
#include <string>
#include <fstream>
#include <unordered_map>
namespace RoadRunner{
	namespace utils{
		struct Property{
			char* name;

			virtual void setValue(std::string&) = 0;
			virtual void writeValue(std::ostream& stream) = 0;
		};

		struct ShortProperty : public Property{
			uint16_t* value;

			ShortProperty(char* name, uint16_t* value){
				this->name = name;
				this->value = value;
			}

			void setValue(std::string& value){
				*this->value = std::stoi(value) & 0xffff;
			}

			void writeValue(std::ostream& stream){
				stream << this->name << ":" << *this->value;
			}
		};
		
		struct UnsignedIntegerProperty : public Property{
			uint32_t* value;
			UnsignedIntegerProperty(char* name, uint32_t* value){
				this->name = name;
				this->value = value;
			}

			void setValue(std::string& value){
				*this->value = std::stoul(value);
			}

			void writeValue(std::ostream& stream){
				stream << this->name << ":" << *this->value;
			}
		};

		struct IntegerProperty : public Property{
			int* value;

			IntegerProperty(char* name, int* value){
				this->name = name;
				this->value = value;
			}

			void setValue(std::string& value){
				*this->value = std::stoi(value);
			}

			void writeValue(std::ostream& stream){
				stream << this->name << ":" << *this->value;
			}
		};

		struct BooleanProperty : public Property{
			bool* value;

			BooleanProperty(char* name, bool* value){
				this->name = name;
				this->value = value;
			}

			void setValue(std::string& value){
				*this->value = value == "true";
			}

			void writeValue(std::ostream& stream){
				stream << this->name << ":" << ((*this->value) ? "true" : "false");
			}

		};

		class Properties
		{
			public:
				char* filename;
				std::unordered_map<std::string, Property*> properties;
				Properties(char* filename, size_t size, Property** array){
					this->filename = filename;
					for(int i = 0; i < size; ++i){
						if(array[i]){
							this->properties[array[i]->name] = array[i];
						}
						
					}

					std::ifstream in(filename);
					if(in.good()){
						std::string key;
						std::string value;
						while(std::getline(std::getline(in, key, ':'), value)){
							Property* prop = this->properties[key];
							if(prop){
								printf("%p\n", prop);
								prop->setValue(value);
							}
						}
					}

					std::ofstream out(filename);
					for(int i = 0; i < size; ++i){
						array[i]->writeValue(out);
						out << "\n";
					}
					in.close();
					out.close();
				}
		};
	}
}