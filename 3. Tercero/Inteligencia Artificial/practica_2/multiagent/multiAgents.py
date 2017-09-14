# multiAgents.py
# --------------
# Licensing Information:  You are free to use or extend these projects for
# educational purposes provided that (1) you do not distribute or publish
# solutions, (2) you retain this notice, and (3) you provide clear
# attribution to UC Berkeley, including a link to
# http://inst.eecs.berkeley.edu/~cs188/pacman/pacman.html
#
# Attribution Information: The Pacman AI projects were developed at UC Berkeley.
# The core projects and autograders were primarily created by John DeNero
# (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# Student side autograding was added by Brad Miller, Nick Hay, and
# Pieter Abbeel (pabbeel@cs.berkeley.edu).


from util import manhattanDistance
from game import Directions
import random, util

from game import Agent

class ReflexAgent(Agent):
    """
      A reflex agent chooses an action at each choice point by examining
      its alternatives via a state evaluation function.

      The code below is provided as a guide.  You are welcome to change
      it in any way you see fit, so long as you don't touch our method
      headers.
    """


    def getAction(self, gameState):
        """
        You do not need to change this method, but you're welcome to.

        getAction chooses among the best options according to the evaluation function.

        Just like in the previous project, getAction takes a GameState and returns
        some Directions.X for some X in the set {North, South, West, East, Stop}
        """
        # Collect legal moves and successor states
        legalMoves = gameState.getLegalActions()

        # Choose one of the best actions
        scores = [self.evaluationFunction(gameState, action) for action in legalMoves]
        bestScore = max(scores)
        bestIndices = [index for index in range(len(scores)) if scores[index] == bestScore]
        chosenIndex = random.choice(bestIndices) # Pick randomly among the best

        "Add more of your code here if you want to"

        return legalMoves[chosenIndex]

    def evaluationFunction(self, currentGameState, action):
        """
        Design a better evaluation function here.

        The evaluation function takes in the current and proposed successor
        GameStates (pacman.py) and returns a number, where higher numbers are better.

        The code below extracts some useful information from the state, like the
        remaining food (newFood) and Pacman position after moving (newPos).
        newScaredTimes holds the number of moves that each ghost will remain
        scared because of Pacman having eaten a power pellet.

        Print out these variables to see what you're getting, then combine them
        to create a masterful evaluation function.
        """
        # Useful information you can extract from a GameState (pacman.py)
        successorGameState = currentGameState.generatePacmanSuccessor(action)
        newPos = successorGameState.getPacmanPosition()
        newFood = successorGameState.getFood()
        newGhostStates = successorGameState.getGhostStates()
        newScaredTimes = [ghostState.scaredTimer for ghostState in newGhostStates]

        "*** YOUR CODE HERE ***"
        #print "state:\n", successorGameState
        #print "CURRENT POS>", currentGameState.getPacmanPosition() ,"\nNEW POS>", newPos,"\nNEW FOOD>\n", newFood
        """ Using MANHATTANDISTANCE + GAMESTATE FACTORS to evaluate the GameState """
        if successorGameState.isWin():
            return float("inf")

        ghostPosition = currentGameState.getGhostPosition(1)
        ghostDistance = util.manhattanDistance(ghostPosition, newPos)
        score = successorGameState.getScore() + ghostDistance

        closestFood = 100
        foodList = newFood.asList()
        for foodPos in foodList:
            dist = util.manhattanDistance(foodPos, newPos)
            if (dist < closestFood):
                closestFood = dist

        if (currentGameState.getNumFood() > successorGameState.getNumFood()):
            score += 100
        if action == Directions.STOP:
            score -= 3
        score -= 3 * closestFood

        capsules = currentGameState.getCapsules()
        if successorGameState.getPacmanPosition() in capsules:
            score += 120

        return score
        #return successorGameState.getScore()

def scoreEvaluationFunction(currentGameState):
    """
      This default evaluation function just returns the score of the state.
      The score is the same one displayed in the Pacman GUI.

      This evaluation function is meant for use with adversarial search agents
      (not reflex agents).
    """
    return currentGameState.getScore()

class MultiAgentSearchAgent(Agent):
    """
      This class provides some common elements to all of your
      multi-agent searchers.  Any methods defined here will be available
      to the MinimaxPacmanAgent, AlphaBetaPacmanAgent & ExpectimaxPacmanAgent.

      You *do not* need to make any changes here, but you can if you want to
      add functionality to all your adversarial search agents.  Please do not
      remove anything, however.

      Note: this is an abstract class: one that should not be instantiated.  It's
      only partially specified, and designed to be extended.  Agent (game.py)
      is another abstract class.
    """

    def __init__(self, evalFn = 'scoreEvaluationFunction', depth = '2'):
        self.index = 0 # Pacman is always agent index 0
        self.evaluationFunction = util.lookup(evalFn, globals())
        self.depth = int(depth)

class MinimaxAgent(MultiAgentSearchAgent):
    """
      Your minimax agent (question 2)
    """
    def getAction(self, gameState):
        """
          Returns the minimax action from the current gameState using self.depth
          and self.evaluationFunction.

          Here are some method calls that might be useful when implementing minimax.

          gameState.getLegalActions(agentIndex):
            Returns a list of legal actions for an agent
            agentIndex=0 means Pacman, ghosts are >= 1

          gameState.generateSuccessor(agentIndex, action):
            Returns the successor game state after an agent takes an action

          gameState.getNumAgents():
            Returns the total number of agents in the game
        """
        "*** YOUR CODE HERE ***"
        return self.maxvalue(gameState, self.depth)[1] #First Call to the maxValue function, to know what the pacman should do
        #util.raiseNotDefined()

    #Minimizing function, as the ghosts are moving
    def minvalue(self, gameState, depth, agentIndex):
        if gameState.isWin() or gameState.isLose() or depth == 0: #If terminal state, evaluate the score and return
            return self.evaluationFunction(gameState), None

        moves = gameState.getLegalActions(agentIndex) #Getting the legal actions of our agent to move
        if agentIndex != (gameState.getNumAgents() - 1): #There are remaining ghosts to be moved
            scores = [(self.minvalue(gameState.generateSuccessor(agentIndex, move), depth, agentIndex + 1), move) for move in moves]
        else: #Finished moving ghosts, time to move the pacman (maxValue)
            scores = [(self.maxvalue(gameState.generateSuccessor(agentIndex, move), depth - 1), move) for move in moves]

        return min(scores)

    #Maximizing function, as the pacman is moving
    def maxvalue(self, gameState, depth, agentIndex=0):
        if gameState.isWin() or gameState.isLose() or depth == 0: #If terminal state, evaluate the score and return
            return self.evaluationFunction(gameState), None

        moves = gameState.getLegalActions(agentIndex) #Getting the legal actions of our agent to move
        scores = [(self.minvalue(gameState.generateSuccessor(agentIndex, move), depth, agentIndex + 1), move) for move in moves]

        return max(scores)

class AlphaBetaAgent(MultiAgentSearchAgent):
    """
      Your minimax agent with alpha-beta pruning (question 3)
    """

    def getAction(self, gameState):
        """
          Returns the minimax action using self.depth and self.evaluationFunction
        """
        "*** YOUR CODE HERE ***"
        #TODO: This agent could and should be running, but autograder.py throws errors still... (dunno where the mistake is)
        alpha = -(float('inf'))
        beta = (float('inf'))
        return self.maxvalue(gameState, self.depth, alpha, beta)[1]
        #util.raiseNotDefined()

    def minvalue(self, gameState, depth, alpha, beta, agentIndex):
        score = float('inf')

        if gameState.isWin() or gameState.isLose() or depth == 0:
            return self.evaluationFunction(gameState), None

        moves = gameState.getLegalActions(agentIndex)
        if agentIndex != (gameState.getNumAgents() - 1):
            for move in moves:
                score = min(score, self.minvalue(gameState.generateSuccessor(agentIndex, move), depth, alpha, beta, agentIndex + 1))
                if score < alpha:
                    return score
                beta = min(beta, score)
        else:
            for move in moves:
                score = min(score, self.maxvalue(gameState.generateSuccessor(agentIndex, move), depth - 1, alpha, beta))
                if score < alpha:
                    return score
                beta = min(beta, score)

        return score

    def maxvalue(self, gameState, depth, alpha, beta, agentIndex=0):
        score = -(float('inf'))

        if gameState.isWin() or gameState.isLose() or depth == 0:
            return self.evaluationFunction(gameState), None

        moves = gameState.getLegalActions(agentIndex)
        scores = []

        for move in moves:
            p = self.minvalue(gameState.generateSuccessor(agentIndex, move), depth, alpha, beta, agentIndex + 1)
            scores.append((p, move))
            score = max(score, p)
            if score > beta:
                return score, None
            alpha = max(alpha, score)

        return max(scores)

class ExpectimaxAgent(MultiAgentSearchAgent):
    """
      Your expectimax agent (question 4)
    """

    def getAction(self, gameState):
        "*** YOUR CODE HERE ***"
        return self.maxvalue(gameState, self.depth)[1] #Starting to look for the move of the pacman in the Expectimax agent
        #util.raiseNotDefined()

    #Expected move function, returns a random choice for the ghosts movements
    def expvalue(self, gameState, depth, agentIndex):
        if gameState.isWin() or gameState.isLose() or depth == 0: #If terminal state, evaluate the score and return
            return self.evaluationFunction(gameState)

        moves = gameState.getLegalActions(agentIndex) #Getting the legal actions of our agent to move
        score = 0.0 #Variable to save the sum of the scores that we got
        prob = 1.0/float(len(moves)) #Probability distribution of the moves
        if agentIndex != (gameState.getNumAgents() - 1): #There are remaining ghosts to be moved
            for move in moves:
                s = self.expvalue(gameState.generateSuccessor(agentIndex, move), depth, agentIndex + 1)
                score += s*prob #Saving the score value based on the chosen probability
        else: #Finished moving ghosts, time to move the pacman (maxValue)
            for move in moves:
                s, m = self.maxvalue(gameState.generateSuccessor(agentIndex, move), depth - 1)
                score += s*prob #Saving the score value based on the chosen probability
        
        return score

    #Maximizing function, as the pacman is moving
    def maxvalue(self, gameState, depth, agentIndex=0):
        if gameState.isWin() or gameState.isLose() or depth == 0: #If terminal state, evaluate the score and return
            return self.evaluationFunction(gameState), None

        moves = gameState.getLegalActions(agentIndex) #Getting the legal actions of our agent to move
        scores = [(self.expvalue(gameState.generateSuccessor(agentIndex, move), depth, agentIndex + 1), move) for move in moves]

        return max(scores)

class BoundedIntelligenceMaxAgent(MultiAgentSearchAgent):
    """
        TEST CLASS, MODIFICATION OF THE EXPECTIMAX CLASS.
    """

    def getAction(self, gameState):
        "*** YOUR CODE HERE ***"
        return self.maxvalue(gameState, self.depth)[1] #Starting to look for the move of the pacman in the BoundedIntelligenceMax agent
        #util.raiseNotDefined()

    #Expected move function, returns a choice for the ghosts movements (wheighted 3/n -> first choice, 1/n -> second till 'n'th)
    def expvalue(self, gameState, depth, agentIndex):
        if gameState.isWin() or gameState.isLose() or depth == 0: #If terminal state, evaluate the score and return
            return self.evaluationFunction(gameState)

        moves = gameState.getLegalActions(agentIndex) #Getting the legal actions of our agent to move
        score = 0.0 #Variable to save the sum of the scores that we got
        sList = []
        
        probs = [1.0/float(len(moves) + 2)] * len(moves) #Defining the probability distribution as asked in the problem
        probs[0] = 3 * probs[0] #First choice must have 3 times the probability as the others

        if agentIndex != (gameState.getNumAgents() - 1): #There are remaining ghosts to be moved
            for move in moves:
                s = self.expvalue(gameState.generateSuccessor(agentIndex, move), depth, agentIndex + 1)
                sList.append(s)
        else: #Finished moving ghosts, time to move the pacman (maxValue)
            for move in moves:
                s, m = self.maxvalue(gameState.generateSuccessor(agentIndex, move), depth - 1)
                sList.append(s)
        
        sList = sorted(sList) #Sorting and pondering the scores to their corresponding probabilities
        for i in range(len(sList) - 1):
            score += sList[i] * probs[i]

        return score

    #Maximizing function, as the pacman is moving
    def maxvalue(self, gameState, depth, agentIndex=0):
        if gameState.isWin() or gameState.isLose() or depth == 0: #If terminal state, evaluate the score and return
            return self.evaluationFunction(gameState), None

        moves = gameState.getLegalActions(agentIndex) #Getting the legal actions of our agent to move
        scores = [(self.expvalue(gameState.generateSuccessor(agentIndex, move), depth, agentIndex + 1), move) for move in moves]

        return max(scores)

def betterEvaluationFunction(currentGameState):
    """
      Your extreme ghost-hunting, pellet-nabbing, food-gobbling, unstoppable
      evaluation function (question 5).

      DESCRIPTION: <write something here so we know what you did>
    """
    "*** YOUR CODE HERE ***"
    util.raiseNotDefined()

# Abbreviation
better = betterEvaluationFunction
