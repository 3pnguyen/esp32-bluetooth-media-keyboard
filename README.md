# esp32-bluetooth-media-keyboard 

## Electronic project that provides the same control as wireless earbuds.

![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white) ![Arduino](https://img.shields.io/badge/-Arduino-00979D?style=for-the-badge&logo=Arduino&logoColor=white) ![Arduino IDE](https://img.shields.io/badge/Arduino%20IDE-%2300979D.svg?style=for-the-badge&logo=Arduino&logoColor=white) ![KiCad](https://img.shields.io/badge/kicad-%23314CB0.svg?style=for-the-badge&logo=kicad&logoColor=white) ![PlatformIO](https://img.shields.io/badge/platformio-%23000.svg?style=for-the-badge&logo=platformio&logoColor=F5822A) ![Onshape](https://img.shields.io/badge/onshape-64bb58?style=for-the-badge&logo=onshape&logoColor=white)

<div align="center">
  <img src="Schematics/Finalized Schematic (V3)/images/irl.jpg" width="450" />
</div>

## ✨ About

This is a repostiory for an electroincs project designed to fit in an Altoids tin with wireless capability to control music playback via Bluetooth. Featuring a 400mAh battery, the circuit also includes a voltage divider + voltage follower setup to reliably measure the battery level & a micro limit switch to trigger sleeping when not in use. The user interface is equiped with 4 push buttons + a compact RGB LED.

When I created the initial prototype (and didn't finish the project), I was not as developed in my electronics skill. Due to being picked up for [Lionstride's Inventeam](https://github.com/3pnguyen/lionstride-inventeam-2026), the project would go under a 6 month hiatus. Drawing closer to the end of the school year, I realized that I could revive the project better than ever. By 6 months, I leveled up my schematic design game, learned to design PCBs, and use programming tools such as PlatformIO. I decided to redesign nearly the entire thing:

<div align="center">
    <table>
        <tr>
            <td> <p> Before: </p> </td>
            <td> <p> After: </p> </td>
        </tr>
        <tr>
            <td> <img src="Schematics/Prototype Schematic (V1)/images/schematic.png" width="450" /> </td>
            <td> <img src="Schematics/Finalized Schematic (V2)/images/Schematic.png" width="450" /> </td>
        </tr>
    </table>
</div>

V2 was a big leap from the initial prototype. But it never ended up being created because it was too expensive. So I went with a hybrid version, V3:

<div align="center">
  <img src="Schematics/Finalized Schematic (V3)/images/schematic.png" width="450" />
</div>

V3 took the pros out of the prototype and V2 - it made the perfect balance of cost and complexity.

It was perfect that the project dragged out the way it did, because I ended up making it better than ever. Other than that, this project has become the benchmark for all of the progress I made in my first year of high school. Other than the project's repository, this is a time capsule for how far I've come - and I'll never forget that.

## 📐 CAD

[Amazing CAD here](https://cad.onshape.com/documents/83f792e68010cb24d3ada2b4/w/ca8c8df538ed234a2d133709/e/c846efb1a51148007d1a6c65?renderMode=0&uiState=69af7c17ebe184b914fd710f)

<div align="center">
    <table>
        <tr>
            <td> <p> Prototype: </p> </td>
            <td> <p> V3: </p> </td>
        </tr>
        <tr>
            <td> <img src="Schematics/Prototype Schematic (V1)/images/cad.png" width="450" /> </td>
            <td> <img src="Schematics/Finalized Schematic (V3)/images/cad.png" width="450" /> </td>
        </tr>
    </table>
</div>

I was too lazy to finish the CAD for V3   <3
