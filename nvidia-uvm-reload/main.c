#include <dbus/dbus.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void) {
  DBusError err;
  dbus_error_init(&err);

  /* connect to the daemon bus */
  DBusConnection *conn = dbus_bus_get(DBUS_BUS_SYSTEM, &err);
  if (!conn) {
    fprintf(stderr, "Failed to get a session DBus connection: %s\n",
            err.message);
    return 1;
  }

  int rv = dbus_bus_request_name(conn, "org.powertools",
                                 DBUS_NAME_FLAG_REPLACE_EXISTING, &err);
  if (rv != DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER) {
    fprintf(stderr, "Failed to request name on bus: %s\n", err.message);
    return 1;
  }

  printf("Starting dbus listener\n");
  while (true) {
    dbus_connection_read_write(conn, 0);
    DBusMessage *msg = dbus_connection_pop_message(conn);

    if (NULL == msg) {
      continue;
    }

    printf("New message!\n");
    if (dbus_message_is_method_call(msg, "org.powertools", "RestartNvidia")) {
      printf("Restarting nvidia module\n");
      int res = system("rmmod nvidia_uvm");
      res |= system("modprobe nvidia_uvm");
      printf("Returning\n");

      DBusMessage *reply = dbus_message_new_method_return(msg);
      if (!dbus_connection_send(conn, reply, NULL)) {
        fprintf(stderr, "Unable to reply\n");
        return 1;
      }

      printf("Exit status is %i\n", res);
      if (res == 0) {
        DBusMessage *msg2 =
            dbus_message_new_signal("/", "org.powertools", "NvidiaRestarted");
        if (NULL == msg2) {
          fprintf(stderr, "NvidiaRestarted message is null\n");
          return 1;
        }

        // send the message and flush the connection
        if (!dbus_connection_send(conn, msg2, NULL)) {
          fprintf(stderr, "Unable to reply with a signal\n");
          return 1;
        }

        dbus_message_unref(msg2);
      }

      dbus_connection_flush(conn);
      dbus_message_unref(reply);
    }

    // free the message
    dbus_message_unref(msg);
  }

  return EXIT_SUCCESS;
}