
#include <legato.h>

#include "mongoose/mongoose.h"

static const char HttpPort[] = "8000";

static void EventHandler(struct mg_connection *connPtr, int ev, void *p)
{
    if (ev == MG_EV_HTTP_REQUEST)
    {
        struct http_message *messagePtr = (struct http_message *)p;
        char reply[100];

        /* Send the reply */
        snprintf(reply, sizeof(reply), "{ \"uri\": \"%.*s\" }\n",
                 (int) messagePtr->uri.len, messagePtr->uri.p);
        mg_printf(connPtr, "HTTP/1.1 200 OK\r\n"
                  "Content-Type: application/json\r\n"
                  "Content-Length: %d\r\n"
                  "\r\n"
                  "%s",
                  (int) strlen(reply), reply);
    }
}

static void Serve(const char *portPtr)
{
    struct mg_mgr manager;
    struct mg_connection *connPtr;

    LE_INFO("Init server on port %s", portPtr);

    mg_mgr_init(&manager, NULL);
    connPtr = mg_bind(&manager, portPtr, EventHandler);
    mg_set_protocol_http_websocket(connPtr);

    /* For each new connection, execute ev_handler in a separate thread */
    //mg_enable_multithreading(connPtr);

    LE_INFO("Starting server on port %s", portPtr);

    for (;;)
    {
        mg_mgr_poll(&manager, 3000);
    }
    mg_mgr_free(&manager);
}

//--------------------------------------------------------------------------------------------------
/**
 * Initialization function for the webServer
 */
//--------------------------------------------------------------------------------------------------
COMPONENT_INIT
{
    Serve(HttpPort);
    LE_FATAL("webServer returned");
}
