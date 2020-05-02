param(
    [Parameter(Mandatory = $true)]
    [ValidateSet("string_matching", "nQueens")]
    [string]$commandToExecute=$Args[0],
    [Parameter(Mandatory = $true)]
    [string]$inputString=$Args[1],
    [Parameter(Mandatory = $true)]
    [ValidateSet("DefaultHeuristic", "BullsAndCows")]
    [string]$heuristic = $Args[2],
    [Parameter(Mandatory = $true)]
    [ValidateSet("Random", "Tournament", "Rws", "Aging")]
    [string]$selectionMethod = $Args[3],
    [Parameter(Mandatory = $true)]
    [ValidateSet("SinglePoint", "TwoPoints", "UniformCrossover")]
    [string]$crossoverMethod = $Args[4]
)

$outputPath = "output/"

Write-Host "Parameters are:"
Write-Host "Command to execute:" $commandToExecute
Write-Host "InputString:" $inputString
Write-Host "Heuristic:" $heuristic
Write-Host "SelectionMethod:" $selectionMethod
Write-Host "CrossoverMethod:" $crossoverMethod

$exe = "$pwd/cmake-build-debug/geneticString.exe"
&$exe $commandToExecute $inputString $heuristic $selectionMethod $crossoverMethod $outputPath
For ($i=0; $i -le 1; $i++) {
    $inputString = -join ((65..90) + (97..122) | Get-Random -Count $(Get-Random -Minimum 4 -Maximum 13)| % {[char]$_});
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
    Write-Host "Properties:"
    $selectionMethod = "Tournament"
    $crossoverMethod = "SinglePoint"
    Write-Host "Heuristic:" $heuristic
    Write-Host "SelectionMethod:" $selectionMethod
    Write-Host "CrossoverMethod:" $crossoverMethod
    &$exe $commandToExecute $inputString $heuristic $selectionMethod $crossoverMethod $outputPath
    Write-Host "=================================================================================="
    Write-Host "Properties:"
    $selectionMethod = "Tournament"
    $crossoverMethod = "TwoPoints"
    Write-Host "Heuristic:" $heuristic
    Write-Host "SelectionMethod:" $selectionMethod
    Write-Host "CrossoverMethod:" $crossoverMethod
    &$exe $commandToExecute $inputString $heuristic $selectionMethod $crossoverMethod $outputPath
    Write-Host "=================================================================================="
    Write-Host "Properties:"
    $selectionMethod = "Tournament"
    $crossoverMethod = "UniformCrossover"
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
    Write-Host "Properties:"
    $selectionMethod = "Rws"
    $crossoverMethod = "TwoPoints"
    Write-Host "Heuristic:" $heuristic
    Write-Host "SelectionMethod:" $selectionMethod
    Write-Host "CrossoverMethod:" $crossoverMethod
    &$exe $commandToExecute $inputString $heuristic $selectionMethod $crossoverMethod $outputPath
    Write-Host "=================================================================================="
    Write-Host "Properties:"
    $selectionMethod = "Rws"
    $crossoverMethod = "UniformCrossover"
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
    Write-Host "Properties:"
    $selectionMethod = "Aging"
    $crossoverMethod = "TwoPoints"
    Write-Host "Heuristic:" $heuristic
    Write-Host "SelectionMethod:" $selectionMethod
    Write-Host "CrossoverMethod:" $crossoverMethod
    &$exe $commandToExecute $inputString $heuristic $selectionMethod $crossoverMethod $outputPath
    Write-Host "=================================================================================="
    Write-Host "Properties:"
    $selectionMethod = "Aging"
    $crossoverMethod = "UniformCrossover"
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
    Write-Host "Properties:"
    $selectionMethod = "Tournament"
    $crossoverMethod = "SinglePoint"
    Write-Host "Heuristic:" $heuristic
    Write-Host "SelectionMethod:" $selectionMethod
    Write-Host "CrossoverMethod:" $crossoverMethod
    &$exe $commandToExecute $inputString $heuristic $selectionMethod $crossoverMethod $outputPath
    Write-Host "=================================================================================="
    Write-Host "Properties:"
    $selectionMethod = "Tournament"
    $crossoverMethod = "TwoPoints"
    Write-Host "Heuristic:" $heuristic
    Write-Host "SelectionMethod:" $selectionMethod
    Write-Host "CrossoverMethod:" $crossoverMethod
    &$exe $commandToExecute $inputString $heuristic $selectionMethod $crossoverMethod $outputPath
    Write-Host "=================================================================================="
    Write-Host "Properties:"
    $selectionMethod = "Tournament"
    $crossoverMethod = "UniformCrossover"
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
    Write-Host "Properties:"
    $selectionMethod = "Rws"
    $crossoverMethod = "TwoPoints"
    Write-Host "Heuristic:" $heuristic
    Write-Host "SelectionMethod:" $selectionMethod
    Write-Host "CrossoverMethod:" $crossoverMethod
    &$exe $commandToExecute $inputString $heuristic $selectionMethod $crossoverMethod $outputPath
    Write-Host "=================================================================================="
    Write-Host "Properties:"
    $selectionMethod = "Rws"
    $crossoverMethod = "UniformCrossover"
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
    Write-Host "Properties:"
    $selectionMethod = "Aging"
    $crossoverMethod = "TwoPoints"
    Write-Host "Heuristic:" $heuristic
    Write-Host "SelectionMethod:" $selectionMethod
    Write-Host "CrossoverMethod:" $crossoverMethod
    &$exe $commandToExecute $inputString $heuristic $selectionMethod $crossoverMethod $outputPath
    Write-Host "=================================================================================="
    Write-Host "Properties:"
    $selectionMethod = "Aging"
    $crossoverMethod = "UniformCrossover"
    Write-Host "Heuristic:" $heuristic
    Write-Host "SelectionMethod:" $selectionMethod
    Write-Host "CrossoverMethod:" $crossoverMethod
    &$exe $commandToExecute $inputString $heuristic $selectionMethod $crossoverMethod $outputPath
    Write-Host "=================================================================================="
}
