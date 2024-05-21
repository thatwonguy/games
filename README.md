# games
This `gh-pages` branch within this repo is being used to test github page deployment from a branch. 

is created as a place to get those github achievements by modifying the contributions.md file by adding your username and link to your github, feel free to submit pull requests, Co-auther a commit into "contributions.md" etc.

More advanced contributions are also welcome.Start off by opening up an issue and lets have a discussion and start devying up the work to see how we can improve and create some games and keep adding features.

--> fork this repo  
--> create your own branch and make modifications  
--> submit a pull request to add back into original host repo and keep building code base  

## Prerequisites for python
1. Create virtual env using conda and activate it
```
conda create -n game python=3.9
conda activate game
```

2. pip install required libraries
```
conda create --name python39 python=3.9
```

## Prerequisites for C++
1. Install the SFML (Simple Fast MultiMedia Library), good for grahpics, sound, handling inputs.
    - download from the [official SFML site](https://www.sfml-dev.org/)
2. On windows use the following to build and run the game file io bash terminal:
```
g++ -std=c++11 -o breakout breakout.cpp -lsfml-graphics -lsfml-window -lsfml-system
./breakout
```
3. On Mac use the following to run and build the file in bash terminal:
```
g++ -std=c++11 -o breakout breakout.cpp -lsfml-graphics -lsfml-window -lsfml-system
./breakout
```
4. On linux use the following to run and build the file in bash terminal:
```
g++ -std=c++11 -o breakout breakout.cpp -lsfml-graphics -lsfml-window -lsfml-system
./breakout
```
Make sure the SFML is correctly installed and the library paths are set up as needed.  
Both the python and C++ versions should provide a similar *breakout* gaming experience!

---
## Testing github pages and github actions:
When utilized from the settings --> pages location, a CI/CD pipeline is in effect and any updates to the branch will update the readme which will then update the website.

- https://thatwonguy.github.io/

