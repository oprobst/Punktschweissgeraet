# Punktschweissgeraet

# Raum f�r Verbesserungen:

   1. Pinbelegung am Microcontroller nicht besonders gut gelegt. 
      MISO/PB4 als Ansteuerung f�r den MOSFET-Treiber ist besonders ungeschickt, da dieser bei Programmierung nun unkontrolliert schaltet.
   2. Im Prinzip w�rde auch ein Transformator reichen, da die Ausl�sung �ber den Microcontroller erfolgt. Dieser k�nnte kurz vorher den 
      Ladestrom mittels Transistor unterbrechen und w�rde so nicht den gesamten Stromkreis kurzschlie�en, sondern nur die Kondensatoren.
   3. Der R/W PIN vom Display ist nicht am Controller angeschlossen. Dadurch sind bei 16MHz unn�tige manuelle Delays zu programmieren.