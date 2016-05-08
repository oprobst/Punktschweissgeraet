# Punktschweissgeraet

# Raum für Verbesserungen:

   1. Pinbelegung am Microcontroller nicht besonders gut gelegt. 
      MISO/PB4 als Ansteuerung für den MOSFET-Treiber ist besonders ungeschickt, da dieser bei Programmierung nun unkontrolliert schaltet.
   2. Im Prinzip würde auch ein Transformator reichen, da die Auslösung über den Microcontroller erfolgt. Dieser könnte kurz vorher den 
      Ladestrom mittels Transistor unterbrechen und würde so nicht den gesamten Stromkreis kurzschließen, sondern nur die Kondensatoren.
   3. Der R/W PIN vom Display ist nicht am Controller angeschlossen. Dadurch sind bei 16MHz unnötige manuelle Delays zu programmieren.