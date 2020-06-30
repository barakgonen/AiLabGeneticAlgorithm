# This script runs regression for all abilities of our genetic engine:
# 1. StringMatching
# 2. nQueens
# 3. KnapSack
# 4. BinPacking
# 5. BaldwinEffect


Write-Host "Running regression on StringMatching problem:"
$stringExamples = @("Hello world!"
#"Hello",
#"fdISBp",
#"kBcpJtaHSO",
#"WRynAoIrxu",
#"WYoCRnrbkQe",
#"wBGDMlOfVTJ",
#"ImDNfLbXCGx",
#"RKHAWkLCQDimsb",

#                    "SEAvYGWUpJqXBy",
#                    "mDRTpqaLPwxQh",
#"World!",
#"HowAreYou",
#"Hi",
#"Bi",
#"AIUGFc",
#"dipFbt",
#"barak",
#"fuvsirPdjYDae",
#"GQHuyIFBAolxagW",
#"VAZnUHwSMoaBxFl",
#"UIEZSTRqKBmJA",

#                    "gAewnxKZHXWrQDFhatu",
#                    "cAXlFgEexsdbyUj",

#"pIHJOB",
#"blgpK",
#"BqpvuWiNKJDeE"

#                    "DotpqXEghvkrx",  COMMENT
#                    "ePnlwsIfYGXLAVu",COMMENT

#"tNqgrmsvaBjKox",
#"EvdVt",
#"gHDE",
#"hseJNbGPHoBMOd",
#"gtiucDfjFoUmwY",
#"DhXGuTbVcpMA",
#"lGPTmRHveSbg",
#"tAxrZPOes",
#"TBJalImUZ",
#"VbTHsrIpt",
#"XEqtBpbJ",

#                    "UXVTquYomKZDWJ", COMMENT
#                    "KfugeWnhZFr",COMMENT

#"EBsXFOqoKP",
#"mdcBYpoEq",
#"HqOhgBcoiM",
#"HJbFYeySsu",
#"cUlqThj",
#"NYFOgtw"
#"prRENBd",
#"IjCeByNpm",
#"IgZW",
#"phsr"
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
    $heuristic = "DefaultHeuristic"
    $selectionMethod = "Tournament"
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
#    Write-Host "Changing crossover method to 2 points"
#    Write-Host "=================================================================================="
#    $crossoverMethod = "TwoPoints"
#    Write-Host "Parameters are:"
#    Write-Host "Command to execute:" $commandToExecute
#    Write-Host "SelectionMethod:" $selectionMethod
#    Write-Host "CrossoverMethod:" $crossoverMethod
#    Write-Host "Heuristic:" $heuristic
#    Write-Host "InputString is:" $inputString
#    Write-Host "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
#    &$exe $commandToExecute $selectionMethod $crossoverMethod $heuristic $inputString $outputPath
#    Write-Host "=================================================================================="
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
#    $heuristic = "BullsAndCows"
#    $crossoverMethod = "SinglePoint"
#    Write-Host "Parameters are:"
#    Write-Host "Command to execute:" $commandToExecute
#    Write-Host "InputString is:" $inputString
#    Write-Host "Heuristic:" $heuristic
#    Write-Host "SelectionMethod:" $selectionMethod
#    Write-Host "CrossoverMethod:" $crossoverMethod
#    &$exe $commandToExecute $selectionMethod $crossoverMethod $heuristic $inputString $outputPath
#    Write-Host "=================================================================================="
#    Write-Host "Changing crossover method to 2 points"
#    Write-Host "=================================================================================="
#    $crossoverMethod = "TwoPoints"
#    Write-Host "Parameters are:"
#    Write-Host "Command to execute:" $commandToExecute
#    Write-Host "SelectionMethod:" $selectionMethod
#    Write-Host "CrossoverMethod:" $crossoverMethod
#    Write-Host "Heuristic:" $heuristic
#    Write-Host "InputString is:" $inputString
#    Write-Host "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
#    &$exe $commandToExecute $selectionMethod $crossoverMethod $heuristic $inputString $outputPath
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
    $heuristic = "DefaultHeuristic"
    $selectionMethod = "Rws"
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
    $heuristic = "DefaultHeuristic"
    $selectionMethod = "Rws"
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
    $heuristic = "DefaultHeuristic"
    $selectionMethod = "Aging"
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

Write-Host "Running nQueens Problem"

$commandToExecute = "nQueens"
$boardSize= "25"
$selectionMethod = "Random"
#$crossoverMethod = "Ox"
#$MutationOperator="Inversion"
#Write-Host "Parameters are:"
#Write-Host "Command to execute:" $commandToExecute
#Write-Host "SelectionMethod:" $selectionMethod
#Write-Host "CrossoverMethod:" $crossoverMethod
#Write-Host "Mutation Operator:" $MutationOperator
#Write-Host "Board Size:" $boardSize
#Write-Host "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
#&$exe $commandToExecute $selectionMethod $crossoverMethod $MutationOperator $boardSize
#Write-Host "=================================================================================="
$crossoverMethod = "Pmx"
$MutationOperator="Exchange"
Write-Host "Parameters are:"
Write-Host "Command to execute:" $commandToExecute
Write-Host "SelectionMethod:" $selectionMethod
Write-Host "CrossoverMethod:" $crossoverMethod
Write-Host "Mutation Operator:" $MutationOperator
Write-Host "Board Size:" $boardSize
Write-Host "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
&$exe $commandToExecute $selectionMethod $crossoverMethod $MutationOperator $boardSize
Write-Host "=================================================================================="
$crossoverMethod = "Pmx"
$MutationOperator="Inversion"
Write-Host "Parameters are:"
Write-Host "Command to execute:" $commandToExecute
Write-Host "SelectionMethod:" $selectionMethod
Write-Host "CrossoverMethod:" $crossoverMethod
Write-Host "Mutation Operator:" $MutationOperator
Write-Host "Board Size:" $boardSize
Write-Host "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
&$exe $commandToExecute $selectionMethod $crossoverMethod $MutationOperator $boardSize
Write-Host "=================================================================================="
#$crossoverMethod = "Ox"
#$MutationOperator="Exchange"
#Write-Host "Parameters are:"
#Write-Host "Command to execute:" $commandToExecute
#Write-Host "SelectionMethod:" $selectionMethod
#Write-Host "CrossoverMethod:" $crossoverMethod
#Write-Host "Mutation Operator:" $MutationOperator
#Write-Host "Board Size:" $boardSize
#Write-Host "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
#&$exe $commandToExecute $selectionMethod $crossoverMethod $MutationOperator $boardSize
Write-Host "=================================================================================="
$selectionMethod = "Rws"
$crossoverMethod = "Ox"
$MutationOperator="Inversion"
Write-Host "Parameters are:"
Write-Host "Command to execute:" $commandToExecute
Write-Host "SelectionMethod:" $selectionMethod
Write-Host "CrossoverMethod:" $crossoverMethod
Write-Host "Mutation Operator:" $MutationOperator
Write-Host "Board Size:" $boardSize
Write-Host "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
&$exe $commandToExecute $selectionMethod $crossoverMethod $MutationOperator $boardSize
Write-Host "=================================================================================="
$crossoverMethod = "Pmx"
$MutationOperator="Exchange"
Write-Host "Parameters are:"
Write-Host "Command to execute:" $commandToExecute
Write-Host "SelectionMethod:" $selectionMethod
Write-Host "CrossoverMethod:" $crossoverMethod
Write-Host "Mutation Operator:" $MutationOperator
Write-Host "Board Size:" $boardSize
Write-Host "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
&$exe $commandToExecute $selectionMethod $crossoverMethod $MutationOperator $boardSize
Write-Host "=================================================================================="
$crossoverMethod = "Pmx"
$MutationOperator="Inversion"
Write-Host "Parameters are:"
Write-Host "Command to execute:" $commandToExecute
Write-Host "SelectionMethod:" $selectionMethod
Write-Host "CrossoverMethod:" $crossoverMethod
Write-Host "Mutation Operator:" $MutationOperator
Write-Host "Board Size:" $boardSize
Write-Host "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
&$exe $commandToExecute $selectionMethod $crossoverMethod $MutationOperator $boardSize
Write-Host "=================================================================================="
$crossoverMethod = "Ox"
$MutationOperator="Exchange"
Write-Host "Parameters are:"
Write-Host "Command to execute:" $commandToExecute
Write-Host "SelectionMethod:" $selectionMethod
Write-Host "CrossoverMethod:" $crossoverMethod
Write-Host "Mutation Operator:" $MutationOperator
Write-Host "Board Size:" $boardSize
Write-Host "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
&$exe $commandToExecute $selectionMethod $crossoverMethod $MutationOperator $boardSize
Write-Host "=================================================================================="
Write-Host "KnapSack"
Write-Host "=================================================================================="
$commandToExecute = "KnapSack"
$selectionMethod = "Random"
$crossoverMethod = "TwoPoints"
Write-Host "Parameters are:"
Write-Host "Command to execute:" $commandToExecute
Write-Host "SelectionMethod:" $selectionMethod
Write-Host "CrossoverMethod:" $crossoverMethod
Write-Host "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
&$exe $commandToExecute $selectionMethod $crossoverMethod
Write-Host "=================================================================================="
$selectionMethod = "Rws"
Write-Host "Parameters are:"
Write-Host "Command to execute:" $commandToExecute
Write-Host "SelectionMethod:" $selectionMethod
Write-Host "CrossoverMethod:" $crossoverMethod
Write-Host "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
&$exe $commandToExecute $selectionMethod $crossoverMethod
Write-Host "=================================================================================="
Write-Host "Bin Packing"
Write-Host "=================================================================================="
$commandToExecute = "BinPacking"
$selectionMethod = "Random"
$crossoverMethod = "Empty"
Write-Host "Parameters are:"
Write-Host "Command to execute:" $commandToExecute
Write-Host "SelectionMethod:" $selectionMethod
Write-Host "CrossoverMethod:" $crossoverMethod
Write-Host "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
&$exe $commandToExecute $selectionMethod $crossoverMethod
Write-Host "=================================================================================="
$selectionMethod = "Rws"
Write-Host "Parameters are:"
Write-Host "Command to execute:" $commandToExecute
Write-Host "SelectionMethod:" $selectionMethod
Write-Host "CrossoverMethod:" $crossoverMethod
Write-Host "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
&$exe $commandToExecute $selectionMethod $crossoverMethod
Write-Host "=================================================================================="
Write-Host "=================================================================================="
Write-Host "Nsga"
Write-Host "=================================================================================="
$commandToExecute = "Nsga"
$selectionMethod = "Aging"
$crossoverMethod = "SinglePoint"
Write-Host "Parameters are:"
Write-Host "Command to execute:" $commandToExecute
Write-Host "SelectionMethod:" $selectionMethod
Write-Host "CrossoverMethod:" $crossoverMethod
Write-Host "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
&$exe $commandToExecute $selectionMethod $crossoverMethod
Write-Host "=================================================================================="
Write-Host "OptimalXOR"
Write-Host "=================================================================================="
$commandToExecute = "OptimalXor"
Write-Host "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
&$exe $commandToExecute
Write-Host "=================================================================================="
