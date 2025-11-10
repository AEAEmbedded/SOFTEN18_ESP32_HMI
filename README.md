# Embedded HMI met Statemachine (SOFTEN18)

Dit project realiseert een embedded Human Machine Interface voor een fictieve machine, draaiend op een ESP32-S3 touchscreen met ESP-IDF en LVGL. Het voldoet aan de eisen uit de opdrachtomschrijving en rubric zoals gepubliceerd in SOFTEN18. De codebase gebruikt modern C++ binnen de embedded beperkingen: geen heapallocatie, geen exceptions en een duidelijke scheiding tussen logica en GUI.

Het meegeleverde basisscherm toont een wit scherm met rode tekst ter bevestiging van de display- en touchdrivers.

---

## Inhoudsopgave

1. Projectoverzicht
2. Hardware en Software
3. Installatie en Buildinstructies
4. Projectstructuur
5. HMI / UI Implementatie
6. Statemachine
7. C++ Ontwerpkeuzes (zelf in te vullen door student)
8. Testplan en Unittesten
9. Bekende Beperkingen
10. Licentie
11. LVGL Resource Protectie en Thread-Safety

---

## Projectoverzicht

Het project bevat:

• initialisatie van het RGB-display, touchcontroller en LVGL-port

• een LVGL-scherm met zowel dynamische als interactieve UI-elementen

• een statemachine met vier tot zes hoofdtoestanden

• minimaal één overgang door de gebruiker

• minimaal één intern gesimuleerd event

• unit-tests voor de logische componenten

• toepassing van embedded C++ volgens de SOFTEN18-richtlijnen

Voorbeeld van de basisrendering die als hardwaretest dient:

```cpp
lv_obj_t *label = lv_label_create(lv_scr_act());
lv_label_set_text(label, "Hello world");
lv_obj_set_style_bg_opa(label, LV_OPA_TRANSP, 0);
lv_obj_set_style_text_color(label, lv_color_hex(0xFF0000), 0);
lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
```

---

## Hardware en Software

### Hardware

• ESP32-S3 RGB touchscreen

### Software

• ESP-IDF 5.x

• VSCode

• C++17

---

## Installatie en Buildinstructies

1. [Installeer VSCode.](https://code.visualstudio.com/)
2. [Installeer en volg de stappen met de vscode extensie voor esp-idf](https://github.com/espressif/vscode-esp-idf-extension/blob/master/README.md)
3. Clone de repository:

   ```bash
   git clone <url>
   cd <project>
   ```
4. Open folder in vscode:

	```bash
	code .
	```
5. Druk op `CTRL+SHIFT+P` -> `Add VS code Configuration folder` om intellisense (code completion) werkend te krijgen.

6. Voilá, nu kan je builden en flashen met het vlam icoontje onder in de balk 

Na flashen verschijnt een wit scherm met rode tekst "hello world".

---

## Projectstructuur

```
/main
    main.cpp
    display_driver/
		display_driver.h
		display_driver.c
    touch_driver/
		touch_driver.h
		touch_driver.c
CMakeLists.txt
README.md
```

### display_driver/

Initialisatie van het LCD-paneel, LVGL-port, allocatie van displaybuffers en koppeling aan LVGL.

### touch_driver/

Initialisatie van de GT911 via I2C en registratie als LVGL input device.

### ui/

Opbouw van het LVGL-scherm en koppeling met logica en statemachine.

### statemachine/

Hier ontwerpt en implementeert de student zelf de toestanden en overgangen volgens de opdrachtcriteria.

### tests/

Unittests voor logische componenten, zoals toestandovergangen en eventafhandeling.

---

## HMI / UI Implementatie

Het project bevat één LVGL-scherm met:

• een interactief element dat een user-trigger activeert
• een dynamisch element dat verandert bij toestandsovergangen
• een duidelijke visuele indicatie van de huidige toestand

De initialisatie verloopt via:

```cpp
ESP_ERROR_CHECK(display_driver_lcd_init(&lcd_panel));
ESP_ERROR_CHECK(touch_driver_init(&bus, &tp_io, &tp));
ESP_ERROR_CHECK(display_driver_lvgl_init(lcd_panel, tp, &lvgl_disp, &lvgl_touch_indev));
```

UI-mutaties worden altijd binnen een LVGL-lock uitgevoerd:

```cpp
lvgl_port_lock(0);
// LVGL mutaties
lvgl_port_unlock();
```

---

## Statemachine

De statemachine moet voldoen aan de eisen uit de opdracht:

• vier tot zes hoofdtoestanden

• minstens één gebruikersgestuurde overgang

• minstens één intern gegenereerde gebeurtenis

• visuele koppeling met de UI

• scheiding van GUI en logica

De volledige ontwerpkeuzes, UML en implementatie worden door de student zelf gemaakt en onderbouwd zoals vereist in het ontwerpdocument.

---

## C++ Ontwerpkeuzes (door student in te vullen)

De opdracht vereist dat de student bewust keuzes maakt in modern embedded C++. Deze README beschrijft ze daarom niet inhoudelijk.

De student moet in het ontwerpdocument zelf onderbouwen:

• welke taalconstructies worden gebruikt

• waarom deze geschikt zijn voor embedded systemen

• hoe memory-management is toegepast

• hoe const-correctness, RAII, enums of andere technieken zijn ingezet

• hoe de scheiding tussen logica en UI is vormgegeven

Deze onderbouwing telt mee in zowel het ontwerpdocument als de reflectie.

---

## Testplan en Unittesten

Het testplanbeschrijft:

• de teststrategie

• scenario’s voor toestandovergangen

• interne events

• foutgevallen

Voorbeelden van relevante tests:

• user-transition van een beginstaat naar een actieve toestand

• intern event dat automatisch een nieuwe toestand activeert

• foutafhandeling en detectie van ongeldige events

Zie: [Documentatie ESP-IDF Unit-testing](https://docs.espressif.com/projects/vscode-esp-idf-extension/en/latest/additionalfeatures/unit-testing.html)

## Bekende Beperkingen

• LVGL-emulatie op PC wordt niet ondersteund

• Touchkalibratie is afhankelijk van gebruikte hardware

• Timings van gesimuleerde interne events kunnen per hardwareconfiguratie variëren

---


## LVGL Resource Protectie en Thread-Safety

LVGL is een single-threaded GUI-engine. De interne datastructuren zijn niet beschermd tegen gelijktijdige toegang. Wanneer meerdere taken tegelijk LVGL-objecten aanpassen, kan dit leiden tot race conditions, inconsistente objectdata of crashes. Omdat ESP-IDF standaard in een multithreaded omgeving draait, gebruikt `esp_lvgl_port` een mutex om exclusieve toegang tot LVGL te garanderen.

LVGL-mutaties moeten daarom altijd worden uitgevoerd binnen:

```cpp
lvgl_port_lock(0);
// LVGL mutaties
lvgl_port_unlock();
```

De lock wordt geïmplementeerd als een FreeRTOS-mutex en zorgt ervoor dat slechts één taak tegelijk wijzigingen uitvoert aan LVGL-widgets. Binnen eventhandlers is een lock meestal niet nodig, omdat LVGL deze in een veilige context aanroept.

### Meer informatie

• LVGL Documentatie: [https://docs.lvgl.io/latest/en/html/porting/os.html](https://docs.lvgl.io/latest/en/html/porting/os.html)

• ESP-IDF LVGL Port: [https://github.com/espressif/esp-bsp/tree/master/components/esp_lvgl_port](https://github.com/espressif/esp-bsp/tree/master/components/esp_lvgl_port)

• LVGL Forum: [https://forum.lvgl.io](https://forum.lvgl.io)


## Licentie

Apache-2.0
---
