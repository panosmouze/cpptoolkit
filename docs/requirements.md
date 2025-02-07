# Functional Requirements

## CtCore (001)

### CtExceptions (001)
| ID             | Description                                                                                                                              |
|----------------|------------------------------------------------------------------------------------------------------------------------------------------|
| FR-001-001-001 | `CtException` must inherit `std::exception` and provide a mechanism to print meaningful messages to the developer.                       |
| FR-001-001-002 | `CtException` must be inherited by all other exceptions used in CppToolkit.                                                              |
| FR-001-001-003 | `CtTypeParseError` should thrown if a type requested cannot be parsed.                                                                   |
| FR-001-001-004 | `CtKeyNotFoundError` should thrown if a rquested key is not linked to a value.                                                           |
| FR-001-001-005 | `CtOutOfRangeError` should thrown if a rquested resource is out of range.                                                                |
| FR-001-001-006 | `CtThreadError` should thrown if a `CtThread` started while it is already running.                                                       |
| FR-001-001-007 | `CtWorkerError` should thrown if a `CtWorker` or a `CtWorkerPool` started while it is already running.                                   |
| FR-001-001-008 | `CtServiceError` should thrown if a `CtService` started while it is already running.                                                     |
| FR-001-001-009 | `CtSocketError` should thrown if a network interface or a port is not available.                                                         |
| FR-001-001-010 | `CtSocketBindError` should thrown if a network port bind failed.                                                                         |
| FR-001-001-011 | `CtSocketPollError` should thrown if the polling to an already initialized socket failed.                                                |
| FR-001-001-012 | `CtSocketReadError` should thrown if reading of an already initialized socket failed.                                                    |
| FR-001-001-013 | `CtSocketWriteError` should thrown if writing of an already initialized socket failed.                                                   |
| FR-001-001-014 | `CtFileReadError` should thrown if reading of a file failed.                                                                             |
| FR-001-001-015 | `CtFileWriteError` should thrown if writing to a file failed.                                                                            |
| FR-001-001-016 | `CtFileParseError` should thrown if parsing an already open file failed.                                                                 |
| FR-001-001-017 | `CtEventAlreadyExistsError` should thrown if a `CtObject` try to register an already registered event.                                   |
| FR-001-001-018 | `CtEventNotExistsError` should thrown if an event is not registered to a `CtObject` but connection or triggering called.                 |

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
| FR-001-003-003 | `CtRawData` should have a default internal buffer size of `2048` bytes if there is no size given by the user.                            |
| FR-001-003-004 | `CtRawData` must provide the functionality to be allocated by another `CtRawData` object.                                                |
| FR-001-003-005 | `CtRawData` must provide a method to free its resources.                                                                                 |
| FR-001-003-006 | `CtRawData` must maintain the size of the data stored and the max size of the data that can be stored.                                   |
| FR-001-003-007 | `CtRawData` must provide a method to set the following byte.                                                                             |
| FR-001-003-008 | `CtRawData` must provide a method to set the following number of bytes given a `CtUInt8*` buffer and its size.                           |
| FR-001-003-009 | `CtRawData` must provide a method to return a pointer to the last N bytes of the internal buffer.                                        |
| FR-001-003-010 | `CtRawData` must provide a method to remove the last N bytes of the internal buffer and modify the size of the data stored accordingly.  |
| FR-001-003-011 | `CtRawData` must provide a method to return the size of the buffer.                                                                      |
| FR-001-003-012 | `CtRawData` must provide a method to return the max size of the buffer.                                                                  |
| FR-001-003-013 | `CtRawData` must provide a method to return a pointer to the internal buffer.                                                            |
| FR-001-003-014 | `CtRawData` must provide a method to copy data to the internal buffer using another `CtRawData` object.                                  |
| FR-001-003-015 | `CtRawData` must provide a method to copy data to the internal buffer using a `CtUInt*` buffer and its size.                             |
| FR-001-003-016 | `CtRawData` must provide a method to reset the internal buffer to zero size.                                                             |
| FR-001-003-017 | `CtRawData` must provide assigment operator.                                                                                             |
| FR-001-003-018 | `CtRawData` must throw `CtOutOfRangeError` if any of its methods try to access a memory out of internal buffer size.                     |

## IO (002)

### CtFileInput (001)
| ID             | Description                                                                                                                              |
|----------------|------------------------------------------------------------------------------------------------------------------------------------------|
| FR-002-001-001 | `CtFileInput` must open a file given its name.                                                                                           |
| FR-002-001-002 | `CtFileInput` must throw `CtFileReadError` if the file cannot be open.                                                                   |
| FR-002-001-003 | `CtFileInput` must provide a method to free its resources and close the file.                                                            |
| FR-002-001-004 | `CtFileInput` must provide a method to read the file.                                                                                    |
| FR-002-001-005 | `CtFileInput` must provide a method to set a delimiter. This delimiter will be used during read to split file into batches.              |
| FR-002-001-005 | `CtFileInput` must use the delimiter provided to split the file data to batches during read method call.                                 |
| FR-002-001-005 | If the delimiter size is zero or the delimiter provided is null the read method call must handle the rest of the file as one batch.      |
| FR-002-001-006 | The read method of `CtFileInput` must get as argument a `CtRawData` and fill it with the next batch of data or till the buffer is full.  |
| FR-002-001-007 | The read method must return `FALSE` in case of end-of-file or `TRUE` in any other case.                                                  |
| FR-002-001-008 | The read method must throw `CtFileReadError` if the file is not open for any reason.                                                     |

### CtFileOutput (002)
| ID             | Description                                                                                                                              |
|----------------|------------------------------------------------------------------------------------------------------------------------------------------|
| FR-002-002-001 | `CtFileOutput` must open a file given its name and the writing mode.                                                                     |
| FR-002-002-002 | Writing mode must be `Append` or `Truncate`. `Append` must append data to a file or create a new one. `Truncate` must create a new file. | 
| FR-002-002-003 | `CtFileOutput` must throw `CtFileWriteError` if the file cannot be open.                                                                 |
| FR-002-002-004 | `CtFileOutput` must provide a method to free its resources and close the file.                                                           | 
| FR-002-002-005 | `CtFileOutput` must provide a method to set a delimiter.                                                                                 | 
| FR-002-002-006 | `CtFileOutput` must provide a method to write data to the file and append the delimiter to them.                                         |
| FR-002-002-007 | If delimiter size is zero or the delimiter provided is null the write method call must write just the data requested with no delimiter.  |
| FR-002-002-008 | `CtFileOutput` must provide a method to write data to the file without appending a delimiter to them.                                    |
| FR-002-002-009 | The write methods of `CtFileOutput` must throw `CtFileWriteError` if the file is not open for any reason.                                |

## Networking (003)

### CtSocketUdp (001)

## Threading (004)

### CtThread (001)

### CtWorker (002)

### CtWorkerPool (003)

### CtService (004)

### CtServicePool (005)

## Time (005)

### Timer (001)

## Utils (006)

### CtConfig (001)

### CtLogger (002)

### CtObject (003)

### CtTask (004)







