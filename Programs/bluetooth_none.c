/*
 * BRLTTY - A background process providing access to the console screen (when in
 *          text mode) for a blind person using a refreshable braille display.
 *
 * Copyright (C) 1995-2014 by The BRLTTY Developers.
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

#include <errno.h>

#include "io_bluetooth.h"
#include "bluetooth_internal.h"
#include "log.h"

BluetoothConnectionExtension *
bthNewConnectionExtension (uint64_t bda) {
  logUnsupportedFunction();
  return NULL;
}

void
bthReleaseConnectionExtension (BluetoothConnectionExtension *bcx) {
}

int
bthOpenChannel (BluetoothConnectionExtension *bcx, uint8_t channel, int timeout) {
  logUnsupportedFunction();
  return 0;
}

int
bthDiscoverChannel (
  uint8_t *channel, BluetoothConnectionExtension *bcx,
  const void *uuidBytes, size_t uuidLength,
  int timeout
) {
  logUnsupportedFunction();
  return 0;
}

BluetoothConnectionExtension *
bthConnect (uint64_t bda, uint8_t channel, int discover, int timeout) {
  logUnsupportedFunction();
  return NULL;
}

void
bthDisconnect (BluetoothConnectionExtension *bcx) {
}

int
bthMonitorInput (BluetoothConnection *connection, AsyncMonitorCallback *callback, void *data) {
  return 0;
}

int
bthAwaitInput (BluetoothConnection *connection, int milliseconds) {
  logUnsupportedFunction();
  return 0;
}

ssize_t
bthReadData (
  BluetoothConnection *connection, void *buffer, size_t size,
  int initialTimeout, int subsequentTimeout
) {
  logUnsupportedFunction();
  return -1;
}

ssize_t
bthWriteData (BluetoothConnection *connection, const void *buffer, size_t size) {
  logUnsupportedFunction();
  return -1;
}

char *
bthObtainDeviceName (uint64_t bda, int timeout) {
  errno = ENOSYS;
  return NULL;
}