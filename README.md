# RFID_over_MQTT
Security PoC - RFID access control system using the MQTT network application layer

Repository status : Maintained

## Description

Implementation of a secure RFID access control over MQTT.
The base firmware could be used for other use cases.

Also used to describe weakness of non-secured implementations.

## Project features

* Flexible by design	: Uses the MQTT pub/sub specificity. Allowing you to easily add any type of device that can push/handle events over the MQTT protocol.
* Secure by design		: Uses SSL to authenticate and encrypt communication across all embedded devices of the MQTT network (WIP).
* Beginner-friendly		: Codded with the arduino development environment. Simplified methods allow to easily get hands on microcontroller programming.
* Low bill cost			: Currently uses low-cost and hackable components.

## Topology

(TODO)

## Security demonstration

(TODO)

## TODO

* 1. Finish the initial documentation for the github repo.
* 2. Publish an example of an embedded MQTT broker.
* 3. Refurbish code and finish all the initial features, including SSL implementation.
* 4. Publish CAD files.

## Credits

* Repo maintainer & dev : Aurélien Hernandez
* Co-worker & dev : Maxime Bailly

