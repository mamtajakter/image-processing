//
// Created by Mamtaj Akter on 2020-03-07.
//

//
// Created by Mamtaj Akter on 2020-03-07.
//

#include "logging.h"

FILE *Logger::logger = NULL;

DataFlowException :: DataFlowException(const char *type, const char *error)
{
    sprintf(msg, "Throwing exception: (%s): %s", type, error);
    Logger::LogEvent(msg);
}

void Logger :: LogEvent(const char *event)
{
    if(Logger::logger == NULL)
    {
        Logger::logger=fopen("Mamtaj_logger", "w");
    }
    fprintf(Logger::logger, "%s\n", event);
}

void Logger :: Finalize()
{
    fclose(logger);
}