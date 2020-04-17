//#define SSL_SECURE

/* Hard-codded Wi-Fi settings for reverse engineering challenge :) */
#define WIFI_CLI_SSID "MQTT_server"
#define WIFI_CLI_PASSWORD ""

/* Hard-codded MQTT credentials for reverse engineering challenge :) */
#define MQTT_CLI_HOST "mqttserver.local"
#ifdef SSL_SECURE
  #define MQTT_CLI_PORT 8883
#else
  #define MQTT_CLI_PORT 1883
#endif

#define MQTT_CLI_USERNAME "es-entry"
#define MQTT_CLI_PASSWORD "es-entry"

#define SHA1_SALT_BEFORE  "HCF2qCQexo"
#define SHA1_SALT_AFTER   "YQG2sPzB5a"

static const char server_fingerprint[] PROGMEM = "85:7F:DE:21:4E:EA:BB:1A:4F:99:E3:71:6C:48:30:FC:C9:DF:01:F5";

static const char client_cert[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIID2DCCAsCgAwIBAgIULjv3UyYOo4z/mIHtqwp4/Y9pdRMwDQYJKoZIhvcNAQEL
BQAwgaYxCzAJBgNVBAYTAkZSMREwDwYDVQQIDAhZdmVsaW5lczEYMBYGA1UEBwwP
TWFudGVzLUxhLVZpbGxlMQ0wCwYDVQQKDARJU1RZMQwwCgYDVQQLDANTRUUxGzAZ
BgNVBAMMEkF1cmVsaWVuIEhFUk5BTkRFWjEwMC4GCSqGSIb3DQEJARYhYXVyZWxp
ZW4uaGVybmFuZGV6QHByb3Rvbm1haWwuY29tMB4XDTIwMDMxMDIwMDM1N1oXDTI1
MDMwOTIwMDM1N1owVzELMAkGA1UEBhMCRlIxETAPBgNVBAgMCFl2ZWxpbmVzMRgw
FgYDVQQHDA9NYW50ZXMtTGEtVmlsbGUxDTALBgNVBAoMBElTVFkxDDAKBgNVBAsM
A1NFRTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAMheydlR7WgwuvHk
vJ9Byc5s6uQo/XYJFJhunMmuaqaff5yRh4Jpnun430sjzzS6zqZAxA+i4dCATPkz
pXx4x1NIzZgRFlbmlIuKZg7QmejUZaBOSZLzCRyBlv4VcPDtTE83LQxxPSkh/1z2
rwEzv0u1/RLWzmWd/8euPA86luCdwR/uC8RZYlSXRr3DcsLVWExuBgqHr9XynoYA
jHpdk5HQSLn7feTH+T2wUlSJGX5Qv1sxb/T4ML/4hHZIeR5nZ9z1hrY69zZ0ZslB
/TSiSPELah3MtE3qEcQZdQ6EaRwxgj5QbBMlWn4ksVFpjkDGfsDOpx429X2xjjXS
TwqGIdsCAwEAAaNMMEowHwYDVR0jBBgwFoAUChZhSTpyqQdbrCkA1UTARnV1Dvkw
CQYDVR0TBAIwADALBgNVHQ8EBAMCBPAwDwYDVR0RBAgwBocEwKgABDANBgkqhkiG
9w0BAQsFAAOCAQEAiNRb2T0tyT9BzLcEnDhK/UcFH5/dSo+6Xlo9MYVDpkIAsBfL
EBbFmzBI3SCUG5y5V54eqwjfHfl3ModoEpp8sEIFaGBNHHQd3EW1GHDgXcoXFzNm
RvJ/kgf3GBV+Xji2gSscRydtWquaOBsyHX4juJnvw4U25HPOS29mqCSZs4Ymuyr6
UplCjLCHB0g9SW301Pm4MdWrmhHoLEfiHtXARWOGLDM09a36Ryqr3cg6i1q9717f
l0vRUwsRKq9jCDXUmYAEH4ELaALSvFR/eqVPbxXk+Cu9eXWHtzQYbMENtf2enjWd
/50xcsRXCMzYEz8gN3C8qmkMogl4PmKuqw/HKA==
-----END CERTIFICATE-----
)EOF";

static const char client_key[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
MIIEpQIBAAKCAQEAyF7J2VHtaDC68eS8n0HJzmzq5Cj9dgkUmG6cya5qpp9/nJGH
gmme6fjfSyPPNLrOpkDED6Lh0IBM+TOlfHjHU0jNmBEWVuaUi4pmDtCZ6NRloE5J
kvMJHIGW/hVw8O1MTzctDHE9KSH/XPavATO/S7X9EtbOZZ3/x648DzqW4J3BH+4L
xFliVJdGvcNywtVYTG4GCoev1fKehgCMel2TkdBIuft95Mf5PbBSVIkZflC/WzFv
9Pgwv/iEdkh5Hmdn3PWGtjr3NnRmyUH9NKJI8QtqHcy0TeoRxBl1DoRpHDGCPlBs
EyVafiSxUWmOQMZ+wM6nHjb1fbGONdJPCoYh2wIDAQABAoIBACfCBzND+mOOJ8oP
pQ3EtBJtsj4LlB9ztc55REsQfMELLPsYNVc/NfUfGM+ED31bA94hQ8YGf+ArVRqt
kMyd+o8gBwuBeHlNz3PQxmdyJNf6LSAd6KNr7gbl/9vyzTJBI78kJ6AsaAJdaJo9
qIQIjJCtT8YJMXMgYrxwaiJrcbyntuRCWLx/vYoSh2RjLeQ9/KeESPNsAx/obtyJ
rROFkxYrE7+z8Cg2a3eDq/dKGbubmG0GPkSAl+EgHhIYEcrR5x9L7TCchP5rrtOX
3YprXTs0/cdhNJXJz+FPRHo10GzjrQus7Qomp3JDnicmm7ykammtoz7CuKJiO4yy
6OBX66ECgYEA5G+4mL9zqaAkovsOIIhut5Zs1XY/ce/D3aIx+UicpEpDx/gTYHvs
VA1hLj4p4AUnfTQiV5GOUFSBx5Ouh1oEkpUntb9DwQ+cu4kPSodziUPGE0bDT/CS
z7ENxjXQ12ToNoNEjQi1UqqaKv8lcm3wP7Eg/c6ITKvDyBT1oRlL3gUCgYEA4Iwe
g9CFxRxjzopa4Igf5al3OCT/HcXTv5xf6A7RQyXh0yYTlbqfkbNbl8jEeG+HM1YY
jwDEvajOZZeYDofqePe9MQXkwOvZYHUPyqYT51BO2ROwudKfq7BQ8YOwwuDclvHk
kDw14qP/X8Ky7L+y6I7ZvYp3UEn1X8fpFxTiJl8CgYEA1DNQCFy4hdbkkZ2jducl
6lbLDNQGhcGTcfvsbkRcdmUiZ8zzuwoC8+Vl4/4NCjPfhff6+tuUltyZnhp64vLl
EoGJ3NQqjVoCX1cnpDUFR3p0so1me4jf6BzxzbFKKfxrldAEyvpO7dba1ZwkXhLw
PUo+embzyD065k9KCXelOT0CgYEA1lZJpm770XvY9UTxnBOzxsgtaaU+889q4SLG
FT9Xlq3pUmCtHyYlvLEkw8y7ZW6n8mPDS3VjVtp0MVszpOMt+EwaBlpm0ZQPSdhT
u48tvoXUzbbS4X1gNkU17mNS7aIwTdEV6Gvgz7bVRDYYDo6pmv0IcLlkTHpcQxIS
t5qSiCcCgYEA0/i8nOqOVqOO335ccHkZATg3uRBHpNidYqugSWMOkHf/qTxhA40x
Oh99CbKkKZ7shUMnlJfcQkYwRt2t4op0wTNx/19QqKszyqnklWt6SnFk4l0+UKfY
GfAeTkf8Rm583ItFU7pAdIL0oh/P+Qga1iyv1hIw4enEIogcg49+rYQ=
-----END RSA PRIVATE KEY-----
)KEY";


static const char ca_cert[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIELzCCAxegAwIBAgIUWr/pH3F8S2Zi7Hv2kxCgIHxCS0cwDQYJKoZIhvcNAQEL
BQAwgaYxCzAJBgNVBAYTAkZSMREwDwYDVQQIDAhZdmVsaW5lczEYMBYGA1UEBwwP
TWFudGVzLUxhLVZpbGxlMQ0wCwYDVQQKDARJU1RZMQwwCgYDVQQLDANTRUUxGzAZ
BgNVBAMMEkF1cmVsaWVuIEhFUk5BTkRFWjEwMC4GCSqGSIb3DQEJARYhYXVyZWxp
ZW4uaGVybmFuZGV6QHByb3Rvbm1haWwuY29tMB4XDTIwMDMxMDE5NDUwMFoXDTI1
MDMwOTE5NDUwMFowgaYxCzAJBgNVBAYTAkZSMREwDwYDVQQIDAhZdmVsaW5lczEY
MBYGA1UEBwwPTWFudGVzLUxhLVZpbGxlMQ0wCwYDVQQKDARJU1RZMQwwCgYDVQQL
DANTRUUxGzAZBgNVBAMMEkF1cmVsaWVuIEhFUk5BTkRFWjEwMC4GCSqGSIb3DQEJ
ARYhYXVyZWxpZW4uaGVybmFuZGV6QHByb3Rvbm1haWwuY29tMIIBIjANBgkqhkiG
9w0BAQEFAAOCAQ8AMIIBCgKCAQEA6Jz3hbHf9kquEzbaAfMmKK6VIqfacQvRmHP5
KWaRxhlXbZ6xTBWbUeAryEC3i3nSJn4HkDThVhreYKvOcoI1iUeavrM6o4uzqH1y
rl9O/YEhtUxPMjh0u3VlP9hl5vcqTTDeENdRFoDbOtsqzYIV94p8ZTIY67cnRPhH
ASptNIzYPOZ18KFVrSQ70hU8WWSFpYgwZRHe/50hqX2BujgSbNNM7AKLyY6clHz3
iGawujT4mulDZwgVTGL1zx7Jc/T9ZVOirxc0t/3a1ty7qXVxQ6V/rL7dkRbUaPQs
rJuFjBo74TpLTAl3oMs7FC04Yue3as50JYvE9GHEDqFo/bHlOQIDAQABo1MwUTAd
BgNVHQ4EFgQUChZhSTpyqQdbrCkA1UTARnV1DvkwHwYDVR0jBBgwFoAUChZhSTpy
qQdbrCkA1UTARnV1DvkwDwYDVR0TAQH/BAUwAwEB/zANBgkqhkiG9w0BAQsFAAOC
AQEA2ckled+ZHVwc3ZkZXT9jT80/5S/mOYWwlxKYQpJibEQrUG22Ww+Vp56rl/QC
q7QWOXHn8GgudsyyauAfS+OCsIm84kzP9igtqLvQliJPhl+twgnbUyKtStEugxq7
b685jLy6Z91H9Aid2i/LvEK6GeyaBHwBkJnU1+sqwqBq6VobHBLJh2EWP80bLCUU
fsfIKY9z8w2bkWd1ZPpzGBAkwXw4KaAlDqLVMQ/tZrnvFG2RgA5b3nR5GrNJdxsj
8fUAya8u6enjVWzmahPEixnLKbzNuMQ1QXk5xd3+55uBIO9auHtQFrmUiYlNi9LE
pYAPtlEG5y1p55pV6BO1shzqEw==
-----END CERTIFICATE-----
)EOF";