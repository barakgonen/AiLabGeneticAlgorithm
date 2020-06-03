# This script runs regression for all abilities of our genetic engine:
# 1. StringMatching
# 2. nQueens
# 3. KnapSack
# 4. BinPacking
# 5. BaldwinEffect


Write-Host "Running regression on StringMatching problem:"
$stringExamples = @("Hello world!"
"Hello",
"fdISBp",
"kBcpJtaHSO",
"WRynAoIrxu",
"WYoCRnrbkQe",
"wBGDMlOfVTJ",
"ImDNfLbXCGx",
"RKHAWkLCQDimsb",

#                    "SEAvYGWUpJqXBy",
#                    "mDRTpqaLPwxQh",
"World!",
"HowAreYou",
"Hi",
"Bi",
"AIUGFc",
"dipFbt",
"barak",
"fuvsirPdjYDae",
"GQHuyIFBAolxagW",
"VAZnUHwSMoaBxFl",
"UIEZSTRqKBmJA",

#                    "gAewnxKZHXWrQDFhatu",
#                    "cAXlFgEexsdbyUj",

"pIHJOB",
"blgpK",
"BqpvuWiNKJDeE",

#                    "DotpqXEghvkrx",  COMMENT
#                    "ePnlwsIfYGXLAVu",COMMENT

"tNqgrmsvaBjKox",
"EvdVt",
"gHDE",
"hseJNbGPHoBMOd",
"gtiucDfjFoUmwY",
"DhXGuTbVcpMA",
"lGPTmRHveSbg",
"tAxrZPOes",
"TBJalImUZ",
"VbTHsrIpt",
"XEqtBpbJ",

#                    "UXVTquYomKZDWJ", COMMENT
#                    "KfugeWnhZFr",COMMENT

"EBsXFOqoKP",
"mdcBYpoEq",
"HqOhgBcoiM",
"HJbFYeySsu",
"cUlqThj",
"NYFOgtw"
"prRENBd",
"IjCeByNpm",
"IgZW",
"phsr"
)

Write-Host "Building solution for Question3, we have to decide wether defaultheuristic is better than bullsandcows"
Write-Host "=================================================================================="
$outputPath = "tmp\\"
$exe = "$pwd\cmake-build-release\geneticString.exe"

Write-Host "EXE:" $exe
ForEach ($inputString In $stringExamples)
{
    $heuristic = "DefaultHeuristic"
    $selectionMethod = "Random"
    $crossoverMethod = "SinglePoint"
    $commandToExecute = "string_matching"
    Write-Host "Parameters are:"
    Write-Host "Command to execute:" $commandToExecute
    Write-Host "SelectionMethod:" $selectionMethod
    Write-Host "CrossoverMethod:" $crossoverMethod
    Write-Host "Heuristic:" $heuristic
    Write-Host "InputString is:" $inputString
    Write-Host "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    &$exe $commandToExecute $selectionMethod $crossoverMethod $heuristic $inputString $outputPath
    Write-Host "=================================================================================="
    Write-Host "Changing crossover method to 2 points"
    Write-Host "=================================================================================="
    $crossoverMethod = "TwoPoints"
    Write-Host "Parameters are:"
    Write-Host "Command to execute:" $commandToExecute
    Write-Host "SelectionMethod:" $selectionMethod
    Write-Host "CrossoverMethod:" $crossoverMethod
    Write-Host "Heuristic:" $heuristic
    Write-Host "InputString is:" $inputString
    Write-Host "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    &$exe $commandToExecute $selectionMethod $crossoverMethod $heuristic $inputString $outputPath
    Write-Host "=================================================================================="
    Write-Host "Changing crossover method to uniform"
    Write-Host "=================================================================================="
    $crossoverMethod = "UniformCrossover"
    Write-Host "Parameters are:"
    Write-Host "Command to execute:" $commandToExecute
    Write-Host "SelectionMethod:" $selectionMethod
    Write-Host "CrossoverMethod:" $crossoverMethod
    Write-Host "Heuristic:" $heuristic
    Write-Host "InputString is:" $inputString
    Write-Host "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    &$exe $commandToExecute $selectionMethod $crossoverMethod $heuristic $inputString $outputPath
    Write-Host "=================================================================================="
    $heuristic = "BullsAndCows"
    $crossoverMethod = "SinglePoint"
    Write-Host "Parameters are:"
    Write-Host "Command to execute:" $commandToExecute
    Write-Host "InputString is:" $inputString
    Write-Host "Heuristic:" $heuristic
    Write-Host "SelectionMethod:" $selectionMethod
    Write-Host "CrossoverMethod:" $crossoverMethod
    &$exe $commandToExecute $selectionMethod $crossoverMethod $heuristic $inputString $outputPath
    Write-Host "=================================================================================="
    Write-Host "Changing crossover method to 2 points"
    Write-Host "=================================================================================="
    $crossoverMethod = "TwoPoints"
    Write-Host "Parameters are:"
    Write-Host "Command to execute:" $commandToExecute
    Write-Host "SelectionMethod:" $selectionMethod
    Write-Host "CrossoverMethod:" $crossoverMethod
    Write-Host "Heuristic:" $heuristic
    Write-Host "InputString is:" $inputString
    Write-Host "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    &$exe $commandToExecute $selectionMethod $crossoverMethod $heuristic $inputString $outputPath
    Write-Host "=================================================================================="
    Write-Host "Changing crossover method to uniform"
    Write-Host "=================================================================================="
    $crossoverMethod = "UniformCrossover"
    Write-Host "Parameters are:"
    Write-Host "Command to execute:" $commandToExecute
    Write-Host "SelectionMethod:" $selectionMethod
    Write-Host "CrossoverMethod:" $crossoverMethod
    Write-Host "Heuristic:" $heuristic
    Write-Host "InputString is:" $inputString
    Write-Host "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    &$exe $commandToExecute $selectionMethod $crossoverMethod $heuristic $inputString $outputPath
    Write-Host "=================================================================================="
}