/*
 * BRLTTY - A background process providing access to the console screen (when in
 *          text mode) for a blind person using a refreshable braille display.
 *
 * Copyright (C) 1995-2013 by The BRLTTY Developers.
 *
 * BRLTTY comes with ABSOLUTELY NO WARRANTY.
 *
 * This is free software, placed under the terms of the
 * GNU General Public License, as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any
 * later version. Please see the file LICENSE-GPL for details.
 *
 * Web Page: http://mielke.cc/brltty/
 *
 * This software is maintained by Dave Mielke <dave@mielke.cc>.
 */

#include "prologue.h"

#include <string.h>

#include "log.h"
#include "io_generic.h"
#include "gio_internal.h"
#include "io_serial.h"

struct GioHandleStruct {
  SerialDevice *device;
};

static int
disconnectSerialResource (GioHandle *handle) {
  serialCloseDevice(handle->device);
  free(handle);
  return 1;
}

static ssize_t
writeSerialData (GioHandle *handle, const void *data, size_t size, int timeout) {
  return serialWriteData(handle->device, data, size);
}

static int
awaitSerialInput (GioHandle *handle, int timeout) {
  return serialAwaitInput(handle->device, timeout);
}

static ssize_t
readSerialData (
  GioHandle *handle, void *buffer, size_t size,
  int initialTimeout, int subsequentTimeout
) {
  return serialReadData(handle->device, buffer, size,
                        initialTimeout, subsequentTimeout);
}

static int
reconfigureSerialResource (GioHandle *handle, const SerialParameters *parameters) {
  return serialSetParameters(handle->device, parameters);
}

static const GioEndpointMethods gioSerialEndpointMethods = {
  .disconnectResource = disconnectSerialResource,

  .writeData = writeSerialData,
  .awaitInput = awaitSerialInput,
  .readData = readSerialData,

  .reconfigureResource = reconfigureSerialResource
};

static int
isSerialSupported (const GioDescriptor *descriptor) {
  return descriptor->serial.parameters != NULL;
}

static int
testSerialIdentifier (const char **identifier) {
  return isSerialDevice(identifier);
}

static int
connectSerialResource (
  const char *identifier,
  const GioDescriptor *descriptor,
  GioEndpoint *endpoint
) {
  GioHandle *handle = malloc(sizeof(*handle));

  if (handle) {
    memset(handle, 0,sizeof(*handle));

    if ((handle->device = serialOpenDevice(identifier))) {
      if (serialSetParameters(handle->device, descriptor->serial.parameters)) {
        endpoint->handle = handle;
        endpoint->methods = &gioSerialEndpointMethods;
        endpoint->options = descriptor->serial.options;

        gioSetBytesPerSecond(endpoint, descriptor->serial.parameters);
        return 1;
      }

      serialCloseDevice(handle->device);
    }

    free(handle);
  } else {
    logMallocError();
  }

  return 0;
}

const GioResourceEntry gioSerialResourceEntry = {
  .isSupported = isSerialSupported,
  .testIdentifier = testSerialIdentifier,
  .connectResource = connectSerialResource
};
