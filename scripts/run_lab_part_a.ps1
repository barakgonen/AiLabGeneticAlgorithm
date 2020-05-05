$commandToExecute = "string_matching"
$exe = "$pwd/cmake-build-debug/geneticString.exe"

$stringExamples = @("Hello world!",
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
#                    "DotpqXEghvkrx",
                    "tNqgrmsvaBjKox",
#                    "ePnlwsIfYGXLAVu",
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
#                    "UXVTquYomKZDWJ",
#                    "KfugeWnhZFr",
                    "EBsXFOqoKP",
                    "mdcBYpoEq",
                    "HqOhgBcoiM",
                    "HJbFYeySsu",
                    "cUlqThj",
                    "NYFOgtw"
                    "prRENBd",
                    "IjCeByNpm",
                    "IgZW",
                    "phsr")

Write-Host "Building solution for Question3, we have to decide wether defaultheuristic is better than bullsandcows"
Write-Host "=================================================================================="
$outputPath = "tmp\\"
ForEach($inputString In $stringExamples)
{
    $heuristic = "DefaultHeuristic"
    $selectionMethod = "Random"
    $crossoverMethod = "SinglePoint"
    Write-Host "Parameters are:"
    Write-Host "Command to execute:" $commandToExecute
    Write-Host "InputString is:" $inputString
    Write-Host "Heuristic:" $heuristic
    Write-Host "SelectionMethod:" $selectionMethod
    Write-Host "CrossoverMethod:" $crossoverMethod
    Write-Host "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    &$exe $commandToExecute $inputString $heuristic $selectionMethod $crossoverMethod $outputPath
    Write-Host "=================================================================================="
    $heuristic = "BullsAndCows"
    Write-Host "Parameters are:"
    Write-Host "Command to execute:" $commandToExecute
    Write-Host "InputString is:" $inputString
    Write-Host "Heuristic:" $heuristic
    Write-Host "SelectionMethod:" $selectionMethod
    Write-Host "CrossoverMethod:" $crossoverMethod
    &$exe $commandToExecute $inputString $heuristic $selectionMethod $crossoverMethod $outputPath
    Write-Host "=================================================================================="
}

$outputPath = "tmp/Question4/"
Write-Host "Building solution for Question4, we have to decide wether Rws selection is better than what we just got as default random selection"
ForEach($inputString In $stringExamples)
{
#    $inputString = -join ((65..90) + (97..122) | Get-Random -Count $(Get-Random -Minimum 4 -Maximum 15)| % {[char]$_});
    Write-Host "InputString is:" $inputString
    $heuristic = "DefaultHeuristic"
    Write-Host "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    Write-Host "Properties:"
    $selectionMethod = "Random"
    $crossoverMethod = "SinglePoint"
    Write-Host "Heuristic:" $heuristic
    Write-Host "SelectionMethod:" $selectionMethod
    Write-Host "CrossoverMethod:" $crossoverMethod
    &$exe $commandToExecute $inputString $heuristic $selectionMethod $crossoverMethod $outputPath
    Write-Host "=================================================================================="
    Write-Host "Properties:"
    $selectionMethod = "Rws"
    $crossoverMethod = "SinglePoint"
    Write-Host "Heuristic:" $heuristic
    Write-Host "SelectionMethod:" $selectionMethod
    Write-Host "CrossoverMethod:" $crossoverMethod
    &$exe $commandToExecute $inputString $heuristic $selectionMethod $crossoverMethod $outputPath
    Write-Host "=================================================================================="
    $heuristic = "BullsAndCows"
    Write-Host "Properties:"
    $selectionMethod = "Random"
    $crossoverMethod = "SinglePoint"
    Write-Host "Heuristic:" $heuristic
    Write-Host "SelectionMethod:" $selectionMethod
    Write-Host "CrossoverMethod:" $crossoverMethod
    &$exe $commandToExecute $inputString $heuristic $selectionMethod $crossoverMethod $outputPath
    Write-Host "=================================================================================="
    Write-Host "Properties:"
    $selectionMethod = "Rws"
    $crossoverMethod = "SinglePoint"
    Write-Host "Heuristic:" $heuristic
    Write-Host "SelectionMethod:" $selectionMethod
    Write-Host "CrossoverMethod:" $crossoverMethod
    &$exe $commandToExecute $inputString $heuristic $selectionMethod $crossoverMethod $outputPath
    Write-Host "=================================================================================="
}

$outputPath = "tmp/Question5/"
Write-Host "Building solution for Question5, we have to decide wether Aging selection is better than what we just got as default random selection"
Write-Host "=================================================================================="
ForEach($inputString In $stringExamples)
{
#    $inputString = -join ((65..90) + (97..122) | Get-Random -Count $(Get-Random -Minimum 4 -Maximum 15)| % {[char]$_});
    Write-Host "InputString is:" $inputString
    $heuristic = "DefaultHeuristic"
    Write-Host "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    Write-Host "Properties:"
    $selectionMethod = "Random"
    $crossoverMethod = "SinglePoint"
    Write-Host "Heuristic:" $heuristic
    Write-Host "SelectionMethod:" $selectionMethod
    Write-Host "CrossoverMethod:" $crossoverMethod
    &$exe $commandToExecute $inputString $heuristic $selectionMethod $crossoverMethod $outputPath
    Write-Host "=================================================================================="
    Write-Host "Properties:"
    $selectionMethod = "Aging"
    $crossoverMethod = "SinglePoint"
    Write-Host "Heuristic:" $heuristic
    Write-Host "SelectionMethod:" $selectionMethod
    Write-Host "CrossoverMethod:" $crossoverMethod
    &$exe $commandToExecute $inputString $heuristic $selectionMethod $crossoverMethod $outputPath
    Write-Host "=================================================================================="
    $heuristic = "BullsAndCows"
    Write-Host "Properties:"
    $selectionMethod = "Random"
    $crossoverMethod = "SinglePoint"
    Write-Host "Heuristic:" $heuristic
    Write-Host "SelectionMethod:" $selectionMethod
    Write-Host "CrossoverMethod:" $crossoverMethod
    &$exe $commandToExecute $inputString $heuristic $selectionMethod $crossoverMethod $outputPath
    Write-Host "=================================================================================="
    Write-Host "Properties:"
    $selectionMethod = "Aging"
    $crossoverMethod = "SinglePoint"
    Write-Host "Heuristic:" $heuristic
    Write-Host "SelectionMethod:" $selectionMethod
    Write-Host "CrossoverMethod:" $crossoverMethod
    &$exe $commandToExecute $inputString $heuristic $selectionMethod $crossoverMethod $outputPath
    Write-Host "=================================================================================="
}

$outputPath = "tmp/Question6/"
Write-Host "Building solution for Question6, we have to decide wether Tournament selection is better than what we just got as default random selection"
Write-Host "=================================================================================="
ForEach($inputString In $stringExamples)
{
#    $inputString = -join ((65..90) + (97..122) | Get-Random -Count $(Get-Random -Minimum 4 -Maximum 15)| % {[char]$_});
    Write-Host "InputString is:" $inputString
    $heuristic = "DefaultHeuristic"
    Write-Host "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    Write-Host "Properties:"
    $selectionMethod = "Random"
    $crossoverMethod = "SinglePoint"
    Write-Host "Heuristic:" $heuristic
    Write-Host "SelectionMethod:" $selectionMethod
    Write-Host "CrossoverMethod:" $crossoverMethod
    &$exe $commandToExecute $inputString $heuristic $selectionMethod $crossoverMethod $outputPath
    Write-Host "=================================================================================="
    Write-Host "Properties:"
    $selectionMethod = "Tournament"
    $crossoverMethod = "SinglePoint"
    Write-Host "Heuristic:" $heuristic
    Write-Host "SelectionMethod:" $selectionMethod
    Write-Host "CrossoverMethod:" $crossoverMethod
    &$exe $commandToExecute $inputString $heuristic $selectionMethod $crossoverMethod $outputPath
    Write-Host "=================================================================================="
    $heuristic = "BullsAndCows"
    Write-Host "Properties:"
    $selectionMethod = "Random"
    $crossoverMethod = "SinglePoint"
    Write-Host "Heuristic:" $heuristic
    Write-Host "SelectionMethod:" $selectionMethod
    Write-Host "CrossoverMethod:" $crossoverMethod
    &$exe $commandToExecute $inputString $heuristic $selectionMethod $crossoverMethod $outputPath
    Write-Host "=================================================================================="
    Write-Host "Properties:"
    $selectionMethod = "Tournament"
    $crossoverMethod = "SinglePoint"
    Write-Host "Heuristic:" $heuristic
    Write-Host "SelectionMethod:" $selectionMethod
    Write-Host "CrossoverMethod:" $crossoverMethod
    &$exe $commandToExecute $inputString $heuristic $selectionMethod $crossoverMethod $outputPath
    Write-Host "=================================================================================="
}

$outputPath = "tmp/Question7/"
Write-Host "Building solution for Question7, we have to decide wether crossover method of 2point / uniform is better than singlepoint"
Write-Host "=================================================================================="
ForEach($inputString In $stringExamples)
{
#    $inputString = -join ((65..90) + (97..122) | Get-Random -Count $(Get-Random -Minimum 4 -Maximum 15)| % {[char]$_});
    Write-Host "InputString is:" $inputString
    $heuristic = "BullsAndCows"
    Write-Host "Properties:"
    $selectionMethod = "Random"
    $crossoverMethod = "SinglePoint"
    Write-Host "Heuristic:" $heuristic
    Write-Host "SelectionMethod:" $selectionMethod
    Write-Host "CrossoverMethod:" $crossoverMethod
    &$exe $commandToExecute $inputString $heuristic $selectionMethod $crossoverMethod $outputPath
    Write-Host "=================================================================================="
    Write-Host "Properties:"
    $selectionMethod = "Random"
    $crossoverMethod = "TwoPoints"
    Write-Host "Heuristic:" $heuristic
    Write-Host "SelectionMethod:" $selectionMethod
    Write-Host "CrossoverMethod:" $crossoverMethod
    &$exe $commandToExecute $inputString $heuristic $selectionMethod $crossoverMethod $outputPath
    Write-Host "=================================================================================="
    Write-Host "Properties:"
    $selectionMethod = "Random"
    $crossoverMethod = "UniformCrossover"
    Write-Host "Heuristic:" $heuristic
    Write-Host "SelectionMethod:" $selectionMethod
    Write-Host "CrossoverMethod:" $crossoverMethod
    &$exe $commandToExecute $inputString $heuristic $selectionMethod $crossoverMethod $outputPath
    Write-Host "=================================================================================="
}
