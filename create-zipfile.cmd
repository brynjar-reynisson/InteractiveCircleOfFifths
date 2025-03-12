copy /Y C:\Users\Lenovo\JUCE\projects\InteractiveCircleOfFifths\Builds\VisualStudio2022\x64\Release\VST3\InteractiveCircleOfFifths.vst3\Contents\x86_64-win\InteractiveCircleOfFifths.vst3 "G:\My Drive\InteractiveCircleOfFifths"
copy /Y "C:\Users\Lenovo\JUCE\projects\InteractiveCircleOfFifths\Builds\VisualStudio2022\x64\Release\Standalone Plugin\InteractiveCircleOfFifths.exe"  "G:\My Drive\InteractiveCircleOfFifths"  

tar -a -c -C "G:\My Drive\InteractiveCircleOfFifths"  -f "G:\My Drive\InteractiveCircleOfFifths\InteractiveCircleOfFifths.zip" InteractiveCircleOfFifths.vst3 InteractiveCircleOfFifths.exe EULA.txt vcredist2015_2017_2019_2022_x64.exe manual.txt
