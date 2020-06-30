//
// Created by barak on 06/06/2020.
//

#include "../include/NsgaSolver.h"

NsgaSolver::NsgaSolver(const SelectionMethod selectionMethod,
                       const CrossoverMethod crossoverMethod,
                       const int numberOfCouples,
                       const int numberOfProccessors)
: AbstractGeneticSolver<Nsga2Struct>(selectionMethod, crossoverMethod, 1000, 5, 0.5, numberOfProccessors, 5, 30, 0,
                                             2000)
, mutateKind{true}
{

}

std::string NsgaSolver::getBestGene() const {
    return std::string();
}

void NsgaSolver::resetCitizenProps(Nsga2Struct &citizen) {
    citizen.resetMembers();
}

void NsgaSolver::setCitizenProps(Nsga2Struct &citizen) {
    for (int j = 0; j < numberOfItems; j++) {
        citizen.items.push_back((double) rand() / 100);
    }
}

void NsgaSolver::init_population() {
    for (int i = 0; i < populationSize; i++) {
        Nsga2Struct citizen;
        resetCitizenProps(citizen);
        setCitizenProps(citizen);

        population.push_back(citizen);
        tmpPopulation.push_back(citizen);
    }
    buffer.resize(GA_POPSIZE);
    tmpBuffer.resize(GA_POPSIZE);
}

int NsgaSolver::start_solve() {
    init_population();

    // run scenerio on initialized population
    auto singleThreadedTotalRuntime = runScenerio();

    // printing results for users
    print_results();
    // if user wants multi-threaded run also
    if (numberOfProccessors != 1) {
        prepareMultiThreadedEnv();
        auto muliThreadedTotalRuntime = runScenerio();

        // printing results for users
        print_results();

        std::string winner = "";
        if (muliThreadedTotalRuntime < singleThreadedTotalRuntime)
            winner = "parallel";
        else
            winner = "single";
        std::cout << "The winner is: " << ((muliThreadedTotalRuntime < singleThreadedTotalRuntime) ? "Parralel" : "Single")
                  << " Multi: " << muliThreadedTotalRuntime << ", single: " << singleThreadedTotalRuntime << std::endl;
    }

    return singleThreadedTotalRuntime;
}

void NsgaSolver::print_results() {

}

void NsgaSolver::mutate(Nsga2Struct &member) {
    if (mutateKind){
        int pos1 = rand() % numberOfItems;
        int pos2 = rand() % numberOfItems;
        while (pos1 == pos2) {
            pos2 = rand() % numberOfItems;
        }
        if (pos2 < pos1) {
            int temp = pos1;
            pos1 = pos2;
            pos2 = temp;
        }
        double x = member.items[pos1];
        for (int i = pos1; i < pos2; i++) {// shifting
            member.items[i] = member.items[i + 1];
        }
        member.items[pos2] = x;
    } else{
        int first = rand() % numberOfItems;
        int second = rand() % numberOfItems;
        while (first == second) {
            second = rand() % numberOfItems;
        }
        double curr = member.items[first];// switch between the tow queens
        member.items[first] = member.items[second];
        member.items[second] = curr;
    }
}

int NsgaSolver::calculateDistanceBetweenTwoCitizens(const Nsga2Struct &citizenOne, const Nsga2Struct &citizenTwo) {
    return 0;
}

void NsgaSolver::handle_specific_elitism(const int index) {

}

int NsgaSolver::elitism(const int esize) {
    for (int i = 0; i < esize; i++) {
        buffer[i].items.clear();
        for (const auto val : population[i].items)
            buffer[i].items.push_back(val);
        buffer[i].fitnessVal = population[i].fitnessVal;
    }
    return 1;
}

int NsgaSolver::mate() {
    int spos, i1, i2;
    int esize = populationSize * GA_ELITRATE;

    elitism(esize);
    for (int i = esize; i < populationSize; i++) {
        switch (selectionMethod) {
            case SelectionMethod::Aging:
                aging(i1, i2, esize);
                break;
            case SelectionMethod::Rws:
                calc_rws(i1, i2);
                break;
            case SelectionMethod::Random:
                random_selection(i1, i2);
                break;
            case SelectionMethod::Tournament:
                i1 = tournament();
                i2 = tournament();
                break;
        }

        switch (crossoverMethod) {
            //                // this is the selection method given in the beginning
            case CrossoverMethod::SinglePoint:
                spos = rand() % numberOfItems;
                set_data_in_buffer_vec_for_single_point_selection(i, i1, i2, spos, numberOfItems);
                //                    buffer[i].ageVal = 0;
                if (rand() < GA_MUTATION)
                    this->mutate(buffer.at(i));
                break;
            case CrossoverMethod::TwoPoints: {
                // choose two positions
                spos = rand() % numberOfItems;
                int spos2 = rand() % numberOfItems;
                // spos will hold the smaller index
                if (spos > spos2) {
                    int temp = spos2;
                    spos2 = spos;
                    spos = temp;
                }
                // two point crossover
                set_data_in_buffer_vec_for_two_points_selection(i, i1, i2, spos, spos2, numberOfItems);
                break;
            }
            case CrossoverMethod::UniformCrossover:
                this->uniform_crossover(i, i1, i2, spos, numberOfItems);
                break;
            case CrossoverMethod::Ox: {
                spos = rand() % numberOfItems;
                buffer[i].items.clear();
                for (int j = 0; j < numberOfItems; j++) {
                    buffer[i].items.push_back(-1);
                }
                for (int j = 0; j < numberOfItems; j++) {
                    if (population[i1].items[j] < numberOfItems / 2)// handling the first half
                        buffer[i].items[j] = population[i1].items[j];
                }
                int k = 0;
                for (int j = 0; j < numberOfItems; j++) {
                    if (population[i2].items[j] >= numberOfItems / 2) {//handling the second half
                        while (buffer[i].items[k] != 0) {
                            k++;
                        }
                        buffer[i].items[k] = population[i2].items[j];
                    }
                }
                buffer[i].ageVal = 0;
            }
                break;
            case CrossoverMethod::Pmx: {
                i1 = rand() % numberOfItems;
                for (int j = 0; j < i1; j++) {
                    buffer[i].items[j] = population[i1].items[j];

                }
                for (int j = i1; j < numberOfItems; j++) {
                    buffer[i].items[j] = population[i2].items[j];
                }
                buffer[i].ageVal = 0;
            }
                break;
            default:
                break;
        }
        if (rand() < GA_MUTATION) {
            mutate(buffer.at(i));
        }
    }
}

void NsgaSolver::aging(int &i1, int &i2, int esize) {
    for (int f = 0, y = 0; y < populationSize && f < populationSize; y++, f++) {
        if (population[f].ageVal <= 5)
            population[f].fitnessVal += 15;
        if (population[f].ageVal < 20) {
            population[f].fitnessVal -= 15;
            if (population[f].fitnessVal < 1)
                population[f].fitnessVal = 1;
            std::copy(population[f].items.begin(), population[f].items.end(), buffer[y].items.begin());
            buffer[y].fitnessVal = population[f].fitnessVal;
            buffer[y].ageVal = population[f].ageVal;
        }
    }
    for (int k = 0; k < populationSize; k++) {
        population[k].ageVal += 1;
        buffer[k].ageVal += 1;
    }
}

void NsgaSolver::print_best() {
    std::cout << "Best Values: ";
    for (int i = 0; i < numberOfItems; i++)
        std::cout << "[" << (population[0].items[i]) << "] , ";
    std::cout << std::endl;
    std::cout << "the Fitness of these values:  (" << population[0].fitnessVal << ")" << std::endl;
}

int NsgaSolver::tournament(int startIndex, int endIndex) {
    int bestGene, random;
    bestGene = rand() % (populationSize);
    for (int i = 0; i < K; i++)
    {
        random = rand() % populationSize;
        if (population[random].fitnessVal < population[bestGene].fitnessVal)
            bestGene = random;
    }
    return bestGene;
}

void NsgaSolver::runGeneticAlgo() {
    for (int i = 0; i < 2000; i++){
        calc_fitness();
        sort_population_by_fitnes();
        print_best();
        if(population.front().fitnessVal == 0){
            break;
        }
        mate();
        swap();
    }
    print_best();
}

void NsgaSolver::setFitnessInRange(const unsigned int startIndex, const unsigned int endIndex) {
    double x;
    double fitness;
    for (int i = startIndex; i < endIndex; i++) {
        fitness = 0;
        for (int j = 0; j < numberOfItems; j++) {
            x = population[i].items[j];
            fitness = fitness + 0.2 * (-x * x) + 0.8 * (-(x - 2) * (x - 2));
        }
        population[i].fitnessVal = fitness / numberOfItems;
    }
}
