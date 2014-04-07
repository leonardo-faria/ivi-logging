#pragma once

#include <unistd.h>
#include <string>
#include <string.h>

namespace logging {

#define LOGGING_WARNING_OUTPUT_PREFIX "Logging: "

enum class LogLevel {
	None, Error, Warning, Info, Debug, Verbose
};

struct AppLogContext;

extern AppLogContext* s_pAppLogContext;

std::string getProcessName(pid_t pid);

struct AppLogContext {
	AppLogContext(const char* id, const char* description) : m_id(id), m_description(description) {
		if (s_pAppLogContext != nullptr) {
			fprintf(
				stderr,
				LOGGING_WARNING_OUTPUT_PREFIX
				"Your application should not define its ID twice using LOG_DEFINE_APP_IDS macro\n");
		}
		s_pAppLogContext = this;
	}
	std::string m_id;
	std::string m_description;
};

void setDefaultAPPIDSIfNeeded();


/**
 * A logging context
 */
class LogContextCommon {

public:
	LogContextCommon(const char* id, const char* contextDescription) : m_id(id), m_description(contextDescription) {
		if (strlen(id) > 4)
			fprintf(
				stderr,
				LOGGING_WARNING_OUTPUT_PREFIX
				"Log IDs should not be longer than 4 characters to be compatible with the DLT : %s\n",
				id);

	}

	~LogContextCommon() {
	}

	const char* getDescription() {
		return m_description;
	}

	const char* getID() {
		return m_id;
	}

	const char* m_id;
	const char* m_description;
	bool m_bRegistered = false;

};

struct LogDataAbstract {

	LogDataAbstract(LogLevel level, const char* fileName, int lineNumber, const char* prettyFunction) {
		m_level = level;
		m_fileName = fileName;
		m_lineNumber = lineNumber;
		m_prettyFunction = prettyFunction;
	}

	LogLevel m_level;
	const char* m_fileName;
	int m_lineNumber;
	const char* m_prettyFunction;

};


}