# RFID_over_MQTT
Security PoC - RFID access control system using the MQTT network application layer

Used for an in-class demonstration of authenticated but non-secured (un-encrypted & uncertified) protocols weaknesses. Allows an attacker to sniff, reverse and replay.

Repository maintenance & developements status : Paused

## Description

Implementation of a secure RFID door access control over MQTT.
The base firmware could be used for other use cases.

Also demonstrate the weakness of authentified but non-secured implementations.

## Project features

* Flexible by design	: Uses the MQTT pub/sub specificity. Allowing you to easily add any type of device that can push/handle events over the MQTT protocol.
* Secure by design		: Uses SSL to certify and encrypt communication across all embedded devices of the MQTT network (WIP).
                       Uses NXP Mifare Desfire instead of Classic, in order to avoid known hardware weaknesses on Classic. Compatible with most french student ID cards.
                       Uses UID instead of memory banks for now (prone to spoofing & clonning issues).
* Beginner-friendly		: Codded with the arduino development environment. Simplified methods allow to easily get hands on microcontroller programming.
* Low bill cost			  : Currently uses low-cost and hackable components (schematics & BOM TODO).

## MQTT pub/sub topology

(TODO)

## Security demonstration

(TODO)

## TODO

* 1. Finish the initial documentation for the github repo.
* 2. Publish an example of an embedded MQTT broker.
* 3. Refurbish code and finish all the initial features, including SSL implementation.
* 4. Publish CAD files (schematics & BOM).

## Credits

* MFRC522 NXP Desfire support library : [JPG-Consulting](https://github.com/JPG-Consulting/rfid-desfire)

* Co-worker & dev : Maxime Bailly
* Repo maintainer & dev : Aurélien Hernandez



