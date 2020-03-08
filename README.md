# PriestGearOptClassic
This is a tool to assist players of World of Warcraft Classic. The tool calculates the optimal gear (Best in Slot, BiS) and single cast "core" spell for a priest given a list of items, priest talents, and an encounter length.

This tool is intended as a more nuanced and globally correct solution to the typical "equivalency points" approach. Equivalency points rank the importance of a particular attribute (mana, +healing, Mp5, intellect, etc.) against one another so that a "best" item may be identified for each slot (head, chest, legs, etc.). However, this approach fails to recognize the stateful dependence each attribute has on one another. For example, the effectiveness of mana depends on the amount of +healing the priest currently has (which makes spells more mana efficient). Equivalency points depend on the current state (attributes) of the priest as well as the particular encounter length. This tool attempts to solve this problem by directly calculating the theoretical optimal healing output of a given encounter for entire sets of gear (an item in each slot), and determining the set of gear which resulted in maximal healing.

## How it Works
The program accepts as primary inputs a database of items, an encounter length, and priest talents. The program will simply iterate through every combination of gear provided and calcuate the resulting attributes of each priest healing spell. A particular gear combination is ranked by "healing score" which is a configurable objective function to be maximized. Specifically:

  healing score = W1 * peak spell HpS + W2 * max throughput spell HpS + W3 * max fast throughput spell HpS

- W1, W2, and W3 are user defined weights (config/opt.csv). 
- Peak spell HpS is the HpS value of the priest spell with the maximum HpS for a single cast (effective healing / MIN( GCD , cast time) ). 
- Max throughput spell HpS is the HpS value of the priest spell which maximizes healing over the entire duration of the selected encounter. This is often synonymous with the spell which uses all of the priests mana over the fight duration.
- Max fast throughput spell HpS is the same as above except the spell must have a cast time <= 2.0s. This is intended to capture the usefulness of fast casts, but im not really sure if its important yet. Currently W3 is set to 0.

The following spells are considered:
- Lesser Heal (Rank 1)
- Lesser Heal (Rank 2)
- Lesser Heal (Rank 3)
- Heal (Rank 1)
- Heal (Rank 2)
- Heal (Rank 3)
- Heal (Rank 4)
- Greater Heal (Rank 1)
- Greater Heal (Rank 2)
- Greater Heal (Rank 3)
- Greater Heal (Rank 4)
- Flash Heal (Rank 1)
- Flash Heal (Rank 2)
- Flash Heal (Rank 3)
- Flash Heal (Rank 4)
- Flash Heal (Rank 5)
- Flash Heal (Rank 6)
- Flash Heal (Rank 7)

The gear combinations and optimal healing spells are then output for the 3 gear combinations which resulted in the highest "healing score".

Note that the current algorithm simply iterates over every possible gear combination. With 18 item slots, given n items in each slot, this results in roughly n^18 combinations, therefore the runtime is polynomial with respect to the number of items for each slot.

## How to Run It
First, configure the input CSVs which define your item list, priest talents, and other configuration parameters.

The tool is configured via various CSV files:
1. data/encounters.csv
  - Contains the list of encounters you would like to choose from and the encounter duration in seconds.
2. data/gear.csv
  - Contains a list of all items which you want the tool to consider when determining the optimal set.
  - The time complexity for this algorithm is approximately O(n^18) where n is the number of items for each slot to be analyzed (more on
  this in the How It Works section). This means the runtime can be very long if you select too many items (limit to 2-3 per slot).
3. data/talents.csv
  The priest talents.
4. config/opt.csv
  Configuration parameters for the objective function which is maximized, more on this in the How It Works section.
  
Now, run the executable from a terminal.

The program will ask for user input of which encounter to analyze then will perform the optimization. See example below:

![Example Input](https://github.com/t-mccawley/PriestGearOptClassic/blob/master/media/example_input.PNG)

This particular example took ~4 min to analyze over 2 million combinations.

![Example Runtime](https://github.com/t-mccawley/PriestGearOptClassic/blob/master/media/example_runtime.PNG)

## Outputs
The program will have two main outputs for each of the top 3 gear combinations with highest "healing score":
1. The priest state (attributes) and optimal healing spells for the gear combination with the highest "healing score".
![Example Output 1](https://github.com/t-mccawley/PriestGearOptClassic/blob/master/media/example_output_1.PNG)
2. The set of gear which is associated with the highest "healing score".
![Example Output 2](https://github.com/t-mccawley/PriestGearOptClassic/blob/master/media/example_output_2.PNG)

<p align="center">
  <img src="https://github.com/t-mccawley/PriestGearOptClassic/blob/master/media/example_output_2.PNG"/>
</p>
