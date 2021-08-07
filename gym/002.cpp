// https://en.wikipedia.org/wiki/Modern_C%2B%2B_Design
// https://www.geeksforgeeks.org/template-specialization-c/

#include <iostream> 
#include <string>


// TODO: Realise this is driver class
template <typename OutputPolicy, typename LanguagePolicy>
class HelloWorld : private OutputPolicy, private LanguagePolicy {
	public:
		// Behavior method. 
		void Run() const {
			// Two policy methods.
			Print(Message()); 
		}
	private:
		using LanguagePolicy::Message; 
		using OutputPolicy::Print;
};


class OutputPolicyWriteToCout { 
	protected:
		template <typename MessageType>
			void Print(MessageType message) const {
				std::cout << message << std::endl; 
			}
};

class LanguagePolicyEnglish { 
	protected:
		std::string Message() const { return "Hello, World!"; } 
};

class LanguagePolicyGerman { 
	protected:
		std::string Message() const { return "Hallo Welt!"; } 
};

int main() {
	// Example 1
	using HelloWorldEnglish = HelloWorld<OutputPolicyWriteToCout, LanguagePolicyEnglish>;
	HelloWorldEnglish hello_world; 
	hello_world.Run(); // Prints "Hello, World!".
	// Example 2
	// Does the same, but uses another language policy.
	using HelloWorldGerman = HelloWorld<OutputPolicyWriteToCout, LanguagePolicyGerman>;
	HelloWorldGerman hello_world2;
	hello_world2.Run(); // Prints "Hallo Welt!". 
}
