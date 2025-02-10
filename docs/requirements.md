# Functional Requirements

## CtCore (001)

### CtExceptions (001)
| ID             | Description                                                                                                                              |
|----------------|------------------------------------------------------------------------------------------------------------------------------------------|
| FR-001-001-001 | `CtException` must inherit `std::exception` and provide a mechanism to print meaningful messages to the developer.                       |
| FR-001-001-002 | `CtException` must be inherited by all other exceptions used in CppToolkit.                                                              |
| FR-001-001-003 | `CtException` and the inherited classes must provide a method to allocate and initialize its resources.                                  |
| FR-001-001-004 | `CtTypeParseError` should thrown if a type requested cannot be parsed.                                                                   |
| FR-001-001-005 | `CtKeyNotFoundError` should thrown if a rquested key is not linked to a value.                                                           |
| FR-001-001-006 | `CtOutOfRangeError` should thrown if a rquested resource is out of range.                                                                |
| FR-001-001-007 | `CtThreadError` should thrown if a `CtThread` started while it is already running.                                                       |
| FR-001-001-008 | `CtWorkerError` should thrown if a `CtWorker` or a `CtWorkerPool` started while it is already running.                                   |
| FR-001-001-009 | `CtServiceError` should thrown if a `CtService` started while it is already running.                                                     |
| FR-001-001-010 | `CtSocketError` should thrown if a socket allocation failed.                                                                             |
| FR-001-001-011 | `CtSocketBindError` should thrown if a network interface or a port is not available.                                                     |
| FR-001-001-012 | `CtSocketPollError` should thrown if the polling to an already initialized socket failed.                                                |
| FR-001-001-013 | `CtSocketReadError` should thrown if reading of an already initialized socket failed.                                                    |
| FR-001-001-014 | `CtSocketWriteError` should thrown if writing of an already initialized socket failed.                                                   |
| FR-001-001-015 | `CtFileReadError` should thrown if reading of a file failed.                                                                             |
| FR-001-001-016 | `CtFileWriteError` should thrown if writing to a file failed.                                                                            |
| FR-001-001-017 | `CtFileParseError` should thrown if parsing an already open file failed.                                                                 |
| FR-001-001-018 | `CtEventAlreadyExistsError` should thrown if a `CtObject` try to register an already registered event.                                   |
| FR-001-001-019 | `CtEventNotExistsError` should thrown if an event is not registered to a `CtObject` but connection or triggering called.                 |

### CtHelpers (002)
| ID             | Description                                                                                                                              |
|----------------|------------------------------------------------------------------------------------------------------------------------------------------|
| FR-001-002-001 | `CtStringHelpers` namespace must provide functions related to string manipulation.                                                       |
| FR-001-002-002 | `CtStringHelpers` namespace must provide function `split` that splits a string into substrings given a delimiter.                        |
| FR-001-002-003 | `CtStringHelpers` namespace must provide function `trim` that removes whitespaces from boths ends of a string.                           |
| FR-001-002-004 | `CtStringHelpers` namespace must provide functions `StrToInt` for string to int transformation.                                          |
| FR-001-002-005 | `CtStringHelpers` namespace must provide functions `StrToUInt` for string to uint transformation.                                        |
| FR-001-002-006 | `CtStringHelpers` namespace must provide functions `StrToFloat` for string to float transformation.                                      |
| FR-001-002-007 | `CtStringHelpers` namespace must provide functions `StrToDouble` for string to double transformation.                                    |
| FR-001-002-100 | `CtSocketHelpers` namespace must provide a function for setting the timeout for poll requests.                                           |
| FR-001-002-101 | `CtSocketHelpers` namespace must provide a function for getting all available network interfaces.                                        |
| FR-001-002-102 | `CtSocketHelpers` namespace must provide a function for getting the address of a specific network interface.                             |
| FR-001-002-103 | `CtSocketHelpers` namespace must provide functions for transforming an interface from string to uint and vice versa.                     |

### CtTypes (003)
| ID             | Description                                                                                                                              |
|----------------|------------------------------------------------------------------------------------------------------------------------------------------|
| FR-001-003-001 | `CppToolkit` core must offer a data type for handling network addresses.                                                                 |
| FR-001-003-002 | `CppToolkit` core must offer a data type `CtRawData` to store and handle data on any type.                                               |
| FR-001-003-003 | `CtRawData` must provide a method to allocate and initialize its resources.                                                              |
| FR-001-003-004 | `CtRawData` should have a default internal buffer size of `2048` bytes if there is no size given by the user.                            |
| FR-001-003-005 | `CtRawData` must provide the functionality to be allocated by another `CtRawData` object.                                                |
| FR-001-003-006 | `CtRawData` must provide a method to free its resources.                                                                                 |
| FR-001-003-007 | `CtRawData` must maintain the size of the data stored and the max size of the data that can be stored.                                   |
| FR-001-003-008 | `CtRawData` must provide a method to set the following byte.                                                                             |
| FR-001-003-009 | `CtRawData` must provide a method to set the following number of bytes given a `CtUInt8*` buffer and its size.                           |
| FR-001-003-010 | `CtRawData` must provide a method to return a pointer to the last N bytes of the internal buffer.                                        |
| FR-001-003-011 | `CtRawData` must provide a method to remove the last N bytes of the internal buffer and modify the size of the data stored accordingly.  |
| FR-001-003-012 | `CtRawData` must provide a method to return the size of the buffer.                                                                      |
| FR-001-003-013 | `CtRawData` must provide a method to return the max size of the buffer.                                                                  |
| FR-001-003-014 | `CtRawData` must provide a method to return a pointer to the internal buffer.                                                            |
| FR-001-003-015 | `CtRawData` must provide a method to copy data to the internal buffer using another `CtRawData` object.                                  |
| FR-001-003-016 | `CtRawData` must provide a method to copy data to the internal buffer using a `CtUInt*` buffer and its size.                             |
| FR-001-003-017 | `CtRawData` must provide a method to reset the internal buffer to zero size.                                                             |
| FR-001-003-018 | `CtRawData` must provide assigment operator.                                                                                             |
| FR-001-003-019 | `CtRawData` must throw `CtOutOfRangeError` if any of its methods try to access a memory out of internal buffer size.                     |

## IO (002)

### CtFileInput (001)
| ID             | Description                                                                                                                              |
|----------------|------------------------------------------------------------------------------------------------------------------------------------------|
| FR-002-001-001 | `CtFileInput` must open a file given its name.                                                                                           |
| FR-002-001-002 | `CtFileInput` must provide a method to allocate and initialize its resources.                                                            |
| FR-002-001-003 | `CtFileInput` must throw `CtFileReadError` if the file cannot be open.                                                                   |
| FR-002-001-004 | `CtFileInput` must provide a method to free its resources and close the file.                                                            |
| FR-002-001-005 | `CtFileInput` must provide a method to read the file.                                                                                    |
| FR-002-001-006 | `CtFileInput` must provide a method to set a delimiter. This delimiter will be used during read to split file into batches.              |
| FR-002-001-007 | `CtFileInput` must use the delimiter provided to split the file data to batches during read method call.                                 |
| FR-002-001-008 | If the delimiter size is zero or the delimiter provided is null the read method call must handle the rest of the file as one batch.      |
| FR-002-001-009 | The read method of `CtFileInput` must get as argument a `CtRawData` and fill it with the next batch of data or till the buffer is full.  |
| FR-002-001-010 | The read method must return `FALSE` in case of end-of-file or `TRUE` in any other case.                                                  |
| FR-002-001-011 | The read method must throw `CtFileReadError` if the file is not open for any reason.                                                     |

### CtFileOutput (002)
| ID             | Description                                                                                                                              |
|----------------|------------------------------------------------------------------------------------------------------------------------------------------|
| FR-002-002-001 | `CtFileOutput` must open a file given its name and the writing mode.                                                                     |
| FR-002-002-002 | `CtFileOutput` must provide a method to allocate and initialize its resources.                                                           |
| FR-002-002-003 | Writing mode must be `Append` or `Truncate`. `Append` must append data to a file or create a new one. `Truncate` must create a new file. | 
| FR-002-002-004 | `CtFileOutput` must throw `CtFileWriteError` if the file cannot be open.                                                                 |
| FR-002-002-005 | `CtFileOutput` must provide a method to free its resources and close the file.                                                           | 
| FR-002-002-006 | `CtFileOutput` must provide a method to set a delimiter.                                                                                 | 
| FR-002-002-007 | `CtFileOutput` must provide a method to write data to the file and append the delimiter to them.                                         |
| FR-002-002-008 | If delimiter size is zero or the delimiter provided is null the write method call must write just the data requested with no delimiter.  |
| FR-002-002-009 | `CtFileOutput` must provide a method to write data to the file without appending a delimiter to them.                                    |
| FR-002-002-010 | The write methods of `CtFileOutput` must throw `CtFileWriteError` if the file is not open for any reason.                                |

## Time (003)

### CtTimer (001)
| ID             | Description                                                                                                                              |
|----------------|------------------------------------------------------------------------------------------------------------------------------------------|
| FR-003-001-001 | `CtTimer` must provide a method to allocate and initialize its resources.                                                                |
| FR-003-001-002 | `CtTimer` must provide a method to free its resources.                                                                                   | 
| FR-003-001-003 | `CtTimer` must provide a method for setting the reference point in millisecons.                                                          |
| FR-003-001-004 | `CtTimer` must provide a method for getting the time passed since the reference point in millisecons.                                    |
| FR-003-001-005 | `CtTimer` must provide a method for getting the milliseconds passed since epoch.                                                         |

## Utils (004)

### CtConfig (001)
| ID             | Description                                                                                                                              |
|----------------|------------------------------------------------------------------------------------------------------------------------------------------|
| FR-004-001-001 | `CtConfig` must provide a method to allocate and initialize its resources given a filename.                                              |
| FR-004-001-002 | `CtConfig` must provide a method to free its resources.                                                                                  |
| FR-004-001-003 | `CtConfig` must provide the functionality to save and restore uint, int, float, double and string values to a file.                      |
| FR-004-001-004 | `CtConfig` must maintain and provide an internal map key-value set with varibale's names and values that restored or will be stored.     |
| FR-004-001-005 | `CtConfig` must provide a method to write a configuration loaded in the internal map to a file.                                          |
| FR-004-001-006 | `CtConfig` must provide a method to read a configuration from a file and load it to the internal map.                                    |
| FR-004-001-007 | `CtFileReadError` must be thrown if an error occur with external file while reading.                                                     |
| FR-004-001-008 | `CtFileWriteError` must be thrown if an error occur with external file while writing.                                                    |
| FR-004-001-009 | `CtFileParseError` must be thrown if an error occur parsing the configuration file.                                                      |
| FR-004-001-010 | `CtConfig` must provide a method for parsing values stored in the map given the key.                                                     |
| FR-004-001-011 | `CtConfig` must provide a method for writing values to the map given the key and the value.                                              |
| FR-004-001-012 | `CtKeyNotFoundError` must be thrown if a key requested cannot be found in the internal map.                                              |
| FR-004-001-013 | `CtTypeParseError` must be thrown if a value can not be parsed with the requested type.                                                  |
| FR-004-001-014 | `CtConfig` must provide a method for reseting map deleting all stored values.                                                            |

### CtLogger (002)
| ID             | Description                                                                                                                              |
|----------------|------------------------------------------------------------------------------------------------------------------------------------------|
| FR-004-002-001 | `CtLogger` must provide a method to allocate and initialize its resources given the Log level and a name or an identifier for the logger.|
| FR-004-002-002 | `CtLogger` must provide a method to free its resources.                                                                                  |
| FR-004-002-003 | `CtLogger` must provide 5 log levels DEBUG, INFO, WARNING, ERROR, CRITICAL.                                                              |
| FR-004-002-004 | `CtLogger` must provide methods to log a message for all the log levels.                                                                 |
| FR-004-002-005 | `CtLogger` must log identifier, log time, log level and the message if the message level is higher or equal to logger level.             |

### CtObject (003)
| ID             | Description                                                                                                                              |
|----------------|------------------------------------------------------------------------------------------------------------------------------------------|
| FR-004-003-001 | `CtObject` should be inherited by other classes to utilize event capabilities.                                                           |
| FR-004-003-002 | `CtObject` must provide a method to allocate and initialize its resources.                                                               |
| FR-004-003-003 | `CtObject` must provide a method to free its resources.                                                                                  |
| FR-004-003-004 | `CtObject` must provide a method to register an event.                                                                                   |
| FR-004-003-005 | `CtEventAlreadyExistsError` must be thrown during register event if the event is already registered.                                     |
| FR-004-003-006 | `CtObject` must provide a method to connect an event with a `CtTask` or a function.                                                      |
| FR-004-003-007 | `CtObject` must provide a method to trigger an event.                                                                                    |
| FR-004-003-008 | `CtEventNotExistsError` must be thrown during connect or trigger event if an event does not exists.                                      |
| FR-004-003-009 | `CtObject` must wait for all running activities to stop before free.                                                                     |
| FR-004-003-010 | `CtObject` must provide a method to wait for all events to run the assigned tasks.                                                       |

## Threading (005)

### CtTask (001)
| ID             | Description                                                                                                                              |
|----------------|------------------------------------------------------------------------------------------------------------------------------------------|
| FR-005-001-001 | `CtTask` must maintain and provide a function call and a callback function either by using another `CtTask` or using functions.          |
| FR-005-001-002 | `CtTask` must provide a method to allocate and initialize its resources.                                                                 |
| FR-005-001-003 | `CtTask` must provide a method to free its resources.                                                                                    |
| FR-005-001-004 | `CtTask` must provide a method to get the task function.                                                                                 |
| FR-005-001-005 | `CtTask` must provide a method to get the callback of the task function.                                                                 |
| FR-005-001-006 | `CtTask` must provide a method to set the task function.                                                                                 |
| FR-005-001-007 | `CtTask` must provide a method to set the callback of the task function.                                                                 |
| FR-005-001-008 | `CtTask` must provide the assigment operator.                                                                                            |

### CtThread (002)
| ID             | Description                                                                                                                              |
|----------------|------------------------------------------------------------------------------------------------------------------------------------------|
| FR-005-002-001 | `CtThread` must manage and host a std::thread.                                                                                           |
| FR-005-002-002 | `CtThread` should be inherited by other classes to utilize thread capabilities.                                                          |
| FR-005-002-003 | `CtThread` must provide a method to allocate and initialize its resources.                                                               |
| FR-005-002-004 | `CtThread` must provide and maintain the status of the thread.                                                                           |
| FR-005-002-005 | `CtThread` must provide a method to get the status of the thread in a thread-safe way.                                                   |
| FR-005-002-006 | `CtThread` must provide a method to set the status of the thread in a thread-safe way.                                                   |
| FR-005-002-007 | `CtThread` must provide a method to start the thread.                                                                                    |
| FR-005-002-008 | `CtThread` must throw `CtThreadError` during start method if the thread is already running.                                              |
| FR-005-002-009 | `CtThread` must provide a method to stop the thread.                                                                                     |
| FR-005-002-010 | `CtThread` during stop method must change the status of the thread to not running and wait for the thread to finish.                     |
| FR-005-002-011 | `CtThread` must provide a method that waits for thread exit and to free its resources.                                                   |
| FR-005-002-012 | `CtThread` must provide a method to join the thread.                                                                                     |
| FR-005-002-013 | `CtThread` must provide a static method to put the current running thread to sleep for a specified duration in milliseconds.             |

### CtWorker (003)
| ID             | Description                                                                                                                              |
|----------------|------------------------------------------------------------------------------------------------------------------------------------------|
| FR-005-003-001 | `CtWorker` must handle the execution of a `CtTask` or a function asynchronously.                                                         |
| FR-005-003-002 | `CtWorker` must provide a method to allocate and initialize its resources.                                                               |
| FR-005-003-003 | `CtWorker` must provide a method to free its resources.                                                                                  |
| FR-005-003-004 | `CtWorker` must provide a method to get the status of the worker in a thread-safe way.                                                   |
| FR-005-003-005 | `CtWorker` must provide a method to set the status of the worker in a thread-safe way.                                                   |
| FR-005-003-006 | `CtWorker` must provide a method to join the task execution.                                                                             |
| FR-005-003-007 | `CtWorker` must provide a method to set the task of the worker.                                                                          |
| FR-005-003-008 | The task of the worker must be set either by `CtTask` object or by function.                                                             |
| FR-005-003-009 | `CtWorker` must provide the functionality of a callback function call uppon task completion.                                             |
| FR-005-003-010 | `CtWorker` must provide a method to run the setted task.                                                                                 |
| FR-005-003-011 | `CtWorker` must throw `CtWorkerError` during the call of either run or set task if the worker is currenlty running another task.         |

### CtWorkerPool (004)
| ID             | Description                                                                                                                              |
|----------------|------------------------------------------------------------------------------------------------------------------------------------------|
| FR-005-004-001 | `CtWorkerPool` must handle the execution of `CtTask` objects or functions asynchronously.                                                |
| FR-005-004-002 | `CtWorkerPool` must maintain a vector of `CtWorker` objetcs and a queue of `CtTask` objects.                                             |
| FR-005-004-003 | `CtWorkerPool` must provide a method to allocate and initialize its resources given the number of `CtWorker` that need to be utilized.   |
| FR-005-004-004 | `CtWorkerPool` must provide a method to free its resources.                                                                              |
| FR-005-004-005 | `CtWorkerPool` must wait for all running activities to stop before closing.                                                              |
| FR-005-004-006 | `CtWorkerPool` must provide a method to add a new task to the queue either by `CtTask` or by function in a thread-safe way.              |
| FR-005-004-007 | `CtWorkerPool` must provide a method to join the execution of all active and queued tasks.                                               |
| FR-005-004-008 | When a `CtWorker` is free, the next available active task must be assigned to it in a thread-safe way.                                   |
| FR-005-004-009 | If no active or queued tasks are available the `CtWorkerPool` should stop running till a new task is added.                              |

### CtService (005)
| ID             | Description                                                                                                                              |
|----------------|------------------------------------------------------------------------------------------------------------------------------------------|
| FR-005-005-001 | `CtService` must handle the execution of a `CtTask` object or a function asynchronously and repeatedly.                                  |
| FR-005-005-002 | `CtService` must provide a method to allocate and initialize all resources needed to support its functionality.                          |
| FR-005-005-003 | `CtService` must provide a method to free its resources.                                                                                 |
| FR-005-005-004 | `CtService` must wait for all running activities to stop before closing.                                                                 |
| FR-005-005-005 | `CtService` must provide a method to start running the service.                                                                          |
| FR-005-005-006 | `CtService` must provide a method to stop running the service.                                                                           |
| FR-005-005-007 | `CtService` must throw `CtServiceError` if a service is started more than once.                                                          |
| FR-005-005-008 | `CtService` should inherit the `CtThread` and run the given tasks repeatedly at constant rates.                                          |
| FR-005-005-009 | `CtService` must maintain a counter representing the number of task executions skipped because they were not yet completed.              |
| FR-005-005-010 | `CtService` must maintain a counter representing the number of tasks that should have been executed.                                     |
| FR-005-005-011 | `CtService` must provide a method to get the ratio of skipped task executions to the total task executions.                              |
| FR-005-005-012 | `CtService` must maintain a variable that represents the minimum time interval between task executions in milliseconds.                  |
| FR-005-005-013 | The interval given for each service must be calculated as an integer multiplier of this minimum interval.                                |

### CtServicePool (006)
| ID             | Description                                                                                                                              |
|----------------|------------------------------------------------------------------------------------------------------------------------------------------|
| FR-005-006-001 | `CtServicePool` must handle the execution of `CtTask` objects or functions asynchronously and repeatedly.                                |
| FR-005-006-002 | `CtServicePool` must provide a method to allocate and initialize all resources needed to support its functionality.                      |
| FR-005-006-003 | `CtServicePool` must provide a method to free its resources.                                                                             |
| FR-005-006-004 | `CtServicePool` must wait for all running activities to stop before closing.                                                             |
| FR-005-006-005 | `CtServicePool` must provide a method to add a service task either by `CtTask` or by functiona call in a thread-safe way.                |
| FR-005-006-006 | `CtServicePool` must provide a method to remove a service task either by `CtTask` or by functiona call in a thread-safe way.             |
| FR-005-006-007 | `CtServicePack` a struct must be used to store tasks' period in number of intervals, identifier and task itself.                         |
| FR-005-006-008 | `CtServicePool` must maintain an internal vector of `CtServicePack` objects.                                                             |
| FR-005-006-009 | `CtServicePool` must provide a method for start running the services.                                                                    |
| FR-005-006-010 | `CtServicePool` must provide a method for stop running the services.                                                                     |
| FR-005-006-011 | `CtServicePool` should inherit the `CtThread` and run the given tasks repeatedly at constant rates.                                      |

## Networking (006)

### CtSocketUdp (001)
| ID             | Description                                                                                                                              |
|----------------|------------------------------------------------------------------------------------------------------------------------------------------|
| FR-006-001-001 | `CtSocketUdp` must provide a method to allocate and initialize all resources needed to support its functionality.                        |
| FR-006-001-002 | `CtSocketUdp` must provide a method to free its resources.                                                                               |
| FR-006-001-003 | `CtSocketError` must be thrown if allocation of `CtSocketUdp` failed.                                                                    |
| FR-006-001-004 | `CtSocketUdp` must provide a method for configuring a socket to subscribe for data.                                                      |
| FR-006-001-005 | `CtSocketUdp` must provide a method for configuring a socket to publish data.                                                            |
| FR-006-001-006 | `CtSocketUdp` must provide a method for polling a socket to read data if available.                                                      |
| FR-006-001-007 | `CtSocketUdp` must provide a method for polling a socket availability to publish data.                                                   |
| FR-006-001-008 | `CtSocketPollError` must be thrown if polling a socket failed.                                                                           |
| FR-006-001-009 | `CtSocketUdp` must provide methods to send data over a publisher socket either using `CtRawData` or `CtUInt8*` buffer.                   |
| FR-006-001-010 | `CtSocketUdp` must provide methods to read data from a subscriber socket either using `CtRawData` or `CtUInt8*` buffer.                  |
| FR-006-001-011 | `CtSocketWriteError` must be thrown if writing data to a socket failed.                                                                  |
| FR-006-001-012 | `CtSocketReadError` must be thrown if reading data from a socket failed.                                                                 |
