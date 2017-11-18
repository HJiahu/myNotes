读 [neural network and deep learning][1]
=============================================
### 基本概念
#### 激活函数
##### Perceptron（感知机）
*	A perceptron takes several **binary** inputs, x1,x2,… and produces a single binary output
*	基本性质：
	*	output = 0 if ∑<sub>j</sub>w<sub>j</sub>x<sub>j</sub>  ≤ threshold else 1
	*	Using the bias instead of the threshold, the perceptron rule can be rewritten:
		*	output = 0 if **w**⋅**x**+b ≤ 0 else 0，w和x为向量
*	Another way perceptrons can be used is to compute the elementary logical functions we usually think of as underlying computation, functions such as AND, OR, and NAND. We can use networks of perceptrons to compute any logical function at all. The reason is that the NAND gate is universal for computation, that is, we can build any computation up out of NAND gates.


##### Sigmoid neurons
*	why not use perceptron
	> a small change in the weights or bias of any single perceptron in the network can sometimes cause the output of that perceptron to completely flip, say from 0 to 1. That flip may then cause the behaviour of the rest of the network to completely change in some very complicated way.
*	the sigmoid neuron has inputs, x1,x2... But instead of being just 0 or 1, these inputs can also take on any values between 0 and 1
*	基本性质
	*	output = σ(**w**⋅**x**+b)，σ为sigmoid函数
	*	σ(z) = 1/(1+e^-z)


### 神经网络的基本原理（简单解释）
*	大致思想  
	1. 定义网络的损失函数（有多种不同的损失函数，这里使用平方损失函数）为：C(w,b) = 1/2n ∑<sub>x</sub> ∥y(x)−a∥^2，x代表任意训练样本；w和b表示网络的所有权值和偏置值;y(x)为x对应的标签（真值），a为网络求得的x的分类结果
	2. 定义Δ**v** = (Δw0,Δw1,Δw2...,Δb0,Δb1,Δb2...)为权值与偏置的变化（偏移量）
	3. 则可得：ΔC≈∇C⋅Δ**v**，∇C为损失函数C在当前网络状态下的梯度
	4. 取 Δ**v** = -η∇C   (η 称之为学习率，η越大则更新粒度越大)
	5. 则可得：ΔC ≈ −η∇C⋅∇C = −η∥∇C∥^2 ≤ 0 
	6. 已知平方损失函数恒大于0，不断的利用1~5更新整个网络中的参数直到ΔC趋近于0，即1~5操作无效即可得网络的最优解（局部或全局）
	7. 上面6个过程中只有∇C是未知的，只要知道了∇C我们就可以更新整个网络，∇C可以使用下面的BP算法求得
		1. 求∇C有更传统的方式，就是根据倒数的定义：∂C/∂wj ≈ (C(w+ϵej)−C(w))/ϵ，但这样每次都需要求一次C，运算量太大

*	stochastic gradient descent （随机梯度下降法，这里的随机指的是随机选取每次参加训练的样本，并使用这些样本求得平均的梯度并更新网络）
	> estimate the gradient ∇C by computing ∇C<sub>x</sub> for a small sample of randomly chosen training inputs. By averaging over this small sample it turns out that we can quickly get a good estimate of the true gradient ∇C∇C, and this helps speed up gradient descent, and thus learning.


#### 反向传播算法（BP）
*	反向传输算法的功能：计算网络中任意w或b关于损失函数的偏导（∂C/∂w和∂C/∂b），所有的∂C/∂w和∂C/∂b就是上面所需的∇C
*	符号说明
	*	w<sup>l</sup><sub>jk</sub>：第`l`层的第`j`个神经元和第`l-1`层的第`k`个神经元之间的连接权重（l和j表示同一层的神经元）；
		*	向量表示法：**w**<sup>l</sup>，**w**是一个矩阵，表示的是第l层神经元与第l-1层神经元之间的所有权重信息，元素(j,k)即为w<sup>l</sup><sub>jk</sub>
	*	b<sup>l</sup><sub>j</sub>：第`l`层第`j`个神经元的偏置值；
	*	a<sup>l</sup><sub>j</sub>：第`l`层第`j`个神经元的输出值（即激活函数的输出值）；
		*	a<sup>l</sup><sub>j</sub> = σ(∑<sub>k</sub>w<sup>l</sup><sub>jk</sub>a<sup>l-1</sup><sub>k</sub>+b<sup>l</sup><sub>j</sub>)；
		*	用向量表示为：**a**<sup>l</sup>=σ(**w**<sup>l</sup>**a**<sup>l-1</sup>+**b**<sup>l</sup>)
	*	为了计算a，我们需要计算一个中间值z<sup>l</sup>，即每个神经元提交给激活函数的值：**z**<sup>l</sup> = **w**<sup>l</sup>**a**<sup>l-1</sup>+**b**<sup>l</sup>
		*	那么可简化a的公式为：**a**<sup>l</sup>=σ(**z**<sup>l</sup>)

*	计算网络损失函数的两个假设
	1. 可以通过对批量训练时获得的损失函数值求平均求得全局损失函数值（需要这条假设是因为每次训练时我们只使用了部分数据进行训练）
	2. 可以通过网络的输出求得损失函数值（这一点很明显，因为我们的损失函数的自变量就是网络的输出）

*	Hadamard(Schur) 积(哈达玛积)：`[1 2] ⊙ [3 4] = [1*2 2*4] = [3 8]`
*	涉及反向传播的四个公式（[证明][2]）
	1. δ<sup>L</sup><sub>j</sub> = ∂C/∂z<sup>L</sup><sub>j</sub> = ∂C/∂a<sup>L</sup><sub>j</sub> · σ′(z<sup>L</sup><sub>j</sub>)    
		> δ是C关于最后一层第j个神经元激活函数输入值 z 的偏导
		> 
		> 使用向量表示C关于最后一层的偏导：δ<sup>L</sup>=∇<sub>a<sup>L</sup></sub>C ⊙ σ′(z<sup>L</sup>)     
		> 如果使用平方损失函数则可进一步推导得：δ<sup>L</sup>=(a<sup>L</sup> - y) ⊙ σ′(z<sup>L</sup>) 
	2. δ<sup>l</sup> = (w<sup>l+1</sup>)<sup>T</sup>δ<sup>l+1</sup> · σ′(z<sup>l</sup>) 
		> 这个公式表明我们可以通过后一层的参数求得 C 对当前层的偏导，这是反向传播算法的核心，可以从网络后面向前求每一层的δ
	3. ∂C/∂b<sup>l</sup><sub>j</sub>=δ<sup>l</sup><sub>j</sub>
		> C关于偏置b的偏导，与公式1思想一致，只不过1是关于神经元输入的
	4. ∂C/∂w<sup>l</sup><sub>jk</sub>=a<sup>l-1</sup><sub>k</sub> δ<sup>l</sup><sub>j</sub>
		> C关于每个w的偏导，3,4中已经涉及到我们需要求的参数


#### BP算法的代码实现
*	network类
	
		# import numpy as np		
		class Network(object):
		
		    # sizes是个数组，分别表示每层网络神经元的个数
		    # 例如[784, 30, 10]，表明输入层有784个元素，隐藏层有30个元素，输出层有10个元素
		    def __init__(self, sizes):
		        self.num_layers = len(sizes)  # 确定网络的层数
		        self.sizes = sizes  # 各层神经元个数
		        # randomn用于创建指定形状的数组，其中元素满足标准正态分布
		        # biases中每一列元素的个数都与sizes对应位置元素值相同
		        self.biases = [np.random.randn(y, 1) for y in sizes[1:]]
		        # 如果sizes=[1,2,3]则sizes[:-1]=[1,2]，sizes[1:]=[2,3]，
		        # zip用于合并列表并生成矩阵，但要注意其对行列的处理
		        # zip(sizes[:-1],sizes[1:]) = [[1,2],[2,3]]
		        self.weights = [np.random.randn(y, x) for x, y in zip(sizes[:-1], sizes[1:])]
		
		    # 这个函数就是测试（分类）函数，给出测试数据a，当前函数将给出a对于各个类别的概率
		    def feedforward(self, a):
		        # 可以认为a是输入层的数据，即一张图片各个像素点的值数组
		        for b, w in zip(self.biases, self.weights):
		            a = sigmoid(np.dot(w, a) + b)
		        return a
		
		    # 训练函数
		    def SGD(self, training_data, epochs, mini_batch_size, eta, test_data=None):
		        """Train the neural network using mini-batch stochastic
		        gradient descent.  The ``training_data`` is a list of tuples
		        ``(x, y)`` representing the training inputs and the desired
		        outputs.  The other non-optional parameters are
		        self-explanatory.  If ``test_data`` is provided then the
		        network will be evaluated against the test data after each
		        epoch, and partial progress printed out.  This is useful for
		        tracking progress, but slows things down substantially."""
		        # 如果有测试数据则每次训练完成之后使用测试数据进行测试
		        if test_data: n_test = len(test_data)
		        n = len(training_data)
		        # epochs为训练迭代的次数，每次epoch都将使用所有的数据
		        for j in xrange(epochs):
		            # 打乱训练数据并mini_batch_size设定每次参见训练的数据量
		            random.shuffle(training_data)
		            mini_batches = [
		                training_data[k:k+mini_batch_size]
		                for k in xrange(0, n, mini_batch_size)]
					# 使用一个mini_batch进行一次网络参数更新
		            for mini_batch in mini_batches:
		                self.update_mini_batch(mini_batch, eta)
		            if test_data:
		                print "Epoch {0}: {1} / {2}".format(
		                    j, self.evaluate(test_data), n_test)
		            else:
		                print "Epoch {0} complete".format(j)
		
		    def update_mini_batch(self, mini_batch, eta):
		        """Update the network's weights and biases by applying
		        gradient descent using backpropagation to a single mini batch.
		        The ``mini_batch`` is a list of tuples ``(x, y)``, and ``eta``
		        is the learning rate."""
		        # 创建了与b和w结构相同但元素值均为0的变量nabla_b和nabla_w
		        nabla_b = [np.zeros(b.shape) for b in self.biases]
		        nabla_w = [np.zeros(w.shape) for w in self.weights]
				# 使用一个mini_batch中的样本求δ
		        for x, y in mini_batch:
					# 获得一个样本对网络的微调量
		            delta_nabla_b, delta_nabla_w = self.backprop(x, y)
					# 下面的代码将对mini_batch中每个样本的δ求和，获得最终的δ
		            nabla_b = [nb+dnb for nb, dnb in zip(nabla_b, delta_nabla_b)]
		            nabla_w = [nw+dnw for nw, dnw in zip(nabla_w, delta_nabla_w)]
				# 更新网络参数nw为梯度，eta/len(mini_batch)为步长，
				# 这里不使用平方可能是因为平方损失函数的特殊性，或其他，我还不是很确定
		        self.weights = [w-(eta/len(mini_batch))*nw for w, nw in zip(self.weights, nabla_w)]
		        self.biases = [b-(eta/len(mini_batch))*nb for b, nb in zip(self.biases, nabla_b)]
		
		    # 使用反向传播算法计算网络中每一层w和b的梯度
		    # 或者可以粗略的认为是当前状态下每个神经元对损失函数的倒数
		    def backprop(self, x, y):# x表示的是样本数据（一个样本），y是对应的类别（标签）
		        """Return a tuple "(nabla_b, nabla_w)" representing the
		        gradient for the cost function C_x.  "nabla_b" and
		        "nabla_w" are layer-by-layer lists of numpy arrays, similar
		        to "self.biases" and "self.weights"."""
		        # 所有层的 ∇b 和 ∇w
		        nabla_b = [np.zeros(b.shape) for b in self.biases]
		        nabla_w = [np.zeros(w.shape) for w in self.weights]
		        # feedforward
		        activation = x  #输入层数据
		        activations = [x]  # 保存每一层每个神经元的输出，第一个层为输入x
		        zs = []  # 保存每一层每个神经元的z，即每个神经元激活函数的输入值
		        # b,w在这里代表了每一层神经元的偏置和权值
		        # 下面的for循环用于求上面的 activations 和 zs
		        for b, w in zip(self.biases, self.weights):
		            # 求下一层所有神经元的输入 z
		            z = np.dot(w, activation) + b
		            zs.append(z)
		            # 下一层神经元的输出 a
		            activation = sigmoid(z)
		            activations.append(activation)
		            # backward pass
		        # delta（数组） 是损失函数 C 对最后一层神经元 z 的偏导，这是四个方程中的第一个
		        delta = self.cost_derivative(activations[-1], y) * sigmoid_prime(zs[-1])
		        # 这是第三个方程
		        nabla_b[-1] = delta
		        # 这是第四个方程
		        nabla_w[-1] = np.dot(delta, activations[-2].transpose())
		        # 因为最后一层的数据已经在上面求得，所以下面从倒数第二层开始更新整个网络中的权值和偏置值
		        # 下面的for循环中使用的就是第二个方程，依次从后向前求解每层的∇b 和 ∇w
		        for l in xrange(2, self.num_layers):
		            z = zs[-l]
		            sp = sigmoid_prime(z)
		            # 对非后一层使用第二个方程
		            delta = np.dot(self.weights[-l + 1].transpose(), delta) * sp
		            # 倒数第l层的偏置b对C的偏导，可以认为是倒数第l层b对C的梯度，第三个方程
		            nabla_b[-l] = delta
		            # 倒数第l层的权值对C的梯度，第四个方程
		            nabla_w[-l] = np.dot(delta, activations[-l - 1].transpose())
		        return (nabla_b, nabla_w)
		
		    def evaluate(self, test_data):
		        """Return the number of test inputs for which the neural
		        network outputs the correct result. Note that the neural
		        network's output is assumed to be the index of whichever
		        neuron in the final layer has the highest activation."""
		        test_results = [(np.argmax(self.feedforward(x)), y)
		                        for (x, y) in test_data]
		        return sum(int(x == y) for (x, y) in test_results)
		
		    def cost_derivative(self, output_activations, y):
		        """Return the vector of partial derivatives \partial C_x /
		        \partial a for the output activations."""
		        return (output_activations-y)
		
		#### Miscellaneous functions
		def sigmoid(z):
		    """The sigmoid function."""
		    return 1.0/(1.0+np.exp(-z))
		
		def sigmoid_prime(z):
		    """Derivative of the sigmoid function."""
		    return sigmoid(z)*(1-sigmoid(z))

### 网络的改进
#### 改进激活函数
*	因为sigmoid函数的特点，当输出值趋近于1时sigmoid函数的斜率会趋近于0。此时将整个网络的学习效率会非常低（梯度消失）。这是sigmoid激活函数的缺点
*	cross-entropy 是替代sigmoid做激活函数较为不错的选择，具体原因可以[参考][3]。

#### softmax层
*	现在神经网络中使用的激活函数一般的输出值都在0~1之间，在训练的时候输出层的输出也在0~1之间。一般训练的时候有几个标签就有几个输出值。softmax将输出值转化为概率，具体解释放在后面再说。
*	softmax还可以解决训练时学习速度降低的问题，具体参考[这里][4]

#### 过拟合
*	定义：the model will work well for the existing data, but will fail to generalize to new situations.
*	一个比较形象的解释
	> 一般而言模型中的变量越多其所能表示的现象也越多。如果模型变量有限那么很可能出现其对某些数据拟合的很好，但对新的数据就没有更好的表现，这是因为有限的变量只能抽取有限的数据特征，模型只能抽取已有数据中特有的那些共有特征而不能适应（识别）新数据中的特征。即模型抽取的特征只是整个样本空间的一个子集（即现有数据特有的那一部分），对于新的特征，模型无法再学习（因为无法记忆）也无法再检测。











[1]:http://neuralnetworksanddeeplearning.com/
[2]:http://neuralnetworksanddeeplearning.com/chap2.html#proof_of_the_four_fundamental_equations_(optional)
[3]:http://neuralnetworksanddeeplearning.com/chap3.html#the_cross-entropy_cost_function
[4]:http://neuralnetworksanddeeplearning.com/chap3.html#problem_905066