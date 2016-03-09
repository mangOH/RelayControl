#include "legato.h"
#include "interfaces.h"

#define KEY             "SetGpio"
#define RELAY_NB         8
#define MSG_MAX_LEN      25

static bool RelayStates[RELAY_NB] = {0};

//--------------------------------------------------------------------------------------------------
/**
 * Returns the total number of relays controlled by the system.
 */
//--------------------------------------------------------------------------------------------------
le_result_t relayControl_Count(uint8_t *countPtr)
{
    *countPtr = RELAY_NB;
    return LE_OK;
}

//--------------------------------------------------------------------------------------------------
/**
 * Get the state of a relay.
 */
//--------------------------------------------------------------------------------------------------
le_result_t relayControl_GetState(uint8_t id, bool *statePtr)
{
    if(id == 0 || id > RELAY_NB)
    {
        LE_ERROR("Relay id %u not controlled.", id);
        return LE_OUT_OF_RANGE;
    }

    *statePtr = RelayStates[id-1];
    return LE_OK;
}

//--------------------------------------------------------------------------------------------------
/**
 * Set the state of a relay.
 */
//--------------------------------------------------------------------------------------------------
le_result_t relayControl_SetState(uint8_t id, bool statePtr)
{
    char buffer[MSG_MAX_LEN];

    if(id == 0 || id > RELAY_NB)
    {
        LE_ERROR("Relay id %u not controlled.", id);
        return LE_OUT_OF_RANGE;
    }

    RelayStates[id-1] = statePtr;
    snprintf(buffer, MSG_MAX_LEN, "%d,%d", id, statePtr);
    LE_INFO("Buffer: %s", buffer);
    dataRouter_WriteString(KEY, buffer, time(NULL));

    return LE_OK;
}

//--------------------------------------------------------------------------------------------------
/**
 * Initialization function for the relay component
 */
//--------------------------------------------------------------------------------------------------
COMPONENT_INIT
{        
    dataRouter_SessionStart("","", 0, DATAROUTER_CACHE);
}
