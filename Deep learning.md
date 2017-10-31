读 [neural network and deep learning][1]
=============================================
### 基本概念
#### Perceptron（感知机）
*	A perceptron takes several **binary** inputs, x1,x2,… and produces a single binary output
*	基本性质：
	*	output = 0 if ∑<sub>j</sub>w<sub>j</sub>x<sub>j</sub>  ≤ threshold else 1
	*	Using the bias instead of the threshold, the perceptron rule can be rewritten:
		*	output = 0 if **w**⋅**x**+b ≤ 0 else 0，w和x为向量
*	Another way perceptrons can be used is to compute the elementary logical functions we usually think of as underlying computation, functions such as AND, OR, and NAND. We can use networks of perceptrons to compute any logical function at all. The reason is that the NAND gate is universal for computation, that is, we can build any computation up out of NAND gates.
#### Sigmoid neurons
*	why not use perceptron
	> a small change in the weights or bias of any single perceptron in the network can sometimes cause the output of that perceptron to completely flip, say from 0 to 1. That flip may then cause the behaviour of the rest of the network to completely change in some very complicated way.
*	the sigmoid neuron has inputs, x1,x2... But instead of being just 0 or 1, these inputs can also take on any values between 0 and 1
*	基本性质
	*	output = σ(**w**⋅**x**+b)，σ为sigmoid函数
	*	σ(z) = 1/(1+e^-z)
#### 神经网络的基本原理（简单解释）
*	大致思想  
	1. 定义网络的损失函数为：C(w,b) = 1/2n ∑<sub>x</sub> ∥y(x)−a∥^2，x代表任意训练样本；w和b表示网络的所有权值和偏置值
	2. 定义Δ**v** = (Δw0,Δw1,Δw2...,Δb0,Δb1,Δb2...)为权值与偏置的变化
	3. 则可得：ΔC≈∇C⋅Δv，∇C为损失函数C的梯度
	4. 取 Δ**v** = -η∇C   (η 称之为学习率，η越大则更新粒度越大)
	5. 则可得：ΔC ≈ −η∇C⋅∇C = −η∥∇C∥^2 ≤ 0
	6. 不断的利用1~5更新整个网络中的参数直到ΔC趋近于0，即1~5操作无效即可得网络的最优解（局部或全局）

*	stochastic gradient descent （随机梯度下降法，这里的随机指的是随机选取每次参加训练的数据）
	> estimate the gradient ∇C by computing ∇C<sub>x</sub> for a small sample of randomly chosen training inputs. By averaging over this small sample it turns out that we can quickly get a good estimate of the true gradient ∇C∇C, and this helps speed up gradient descent, and thus learning.

#### 反向传播算法（BP）
*	符号说明
	*	w<sup>l</sup><sub>jk</sub>：第`l`层的第`j`个神经元和第`l-1`层的第`k`个神经元之间的连接权重（l和j表示同一层的神经元）；
		*	向量表示法：**w**<sup>l</sup>，**w**是一个矩阵，元素(j,k)即为w<sup>l</sup><sub>jk</sub>
	*	b<sup>l</sup><sub>j</sub>：第`l`层第`j`个神经元的偏置值；
	*	a<sup>l</sup><sub>j</sub>：第`l`层第`j`个神经元的输出值
		*	a<sup>l</sup><sub>j</sub> = σ(∑<sub>k</sub>w<sup>l</sup><sub>jk</sub>a<sup>l-1</sup><sub>k</sub>+b<sup>l</sup><sub>j</sub>)；
		*	用向量表示为：**a**<sup>l</sup>=σ(**w**<sup>l</sup>**a**<sup>l-1</sup>+**b**<sup>l</sup>)
	*	为了计算a，我们需要计算一个中间值z<sup>l</sup>，即神经元的输入权重之和：**z**<sup>l</sup> = **w**<sup>l</sup>**a**<sup>l-1</sup>+**b**<sup>l</sup>
		*	那么可简化a的公式为：**a**<sup>l</sup>=σ(**z**<sup>l</sup>)

*	计算网络损失函数的两个假设
	1. 整体的损失函数可以由局部损失函数（批量训练时获得的损失函数值）的平均值获得。这是因为每次训练时我们只使用了部分数据进行训练。
	2. 损失函数可以写成网络输出的函数（这一点很明显，因为我们的损失函数的自变量就是网络的输出）

*	Hadamard(Schur) 积(哈达玛积)：`[1 2] ⊙ [3 4] = [1*2 2*4] = [3 8]`
*	涉及反向传播的四个公式
	1. δ<sup>l</sup><sub>j</sub> = ∂C/∂a<sup>l</sup><sub>j</sub> · σ′(z<sup>L</sup><sub>j</sub>)   
		> 这里δ表示的是损失函数C在最后一层中某个神经元在当前参数下的"灵敏度"。  
		> C是a的因变量，而a又是z的因变量，所以δ是C关于最后一层某个z的偏导
		> 
		> 使用向量表示C关于最后一层的偏导：δ<sup>L</sup>=∇<sub>a</sub>C ⊙ σ′(z<sup>L</sup>)     
		> 如果使用平方损失函数则可进一步推导得：δ<sup>L</sup>=(a<sup>L</sup> - y) ⊙ σ′(z<sup>L</sup>) 
	2. δ<sup>l</sup> = (w<sup>l+1</sup>)<sup>T</sup>δ<sup>l+1</sup> · σ′(z<sup>l</sup>) 
		> 这个公式表明我们可以通过后一层的参数求得C对于前一层的偏导，这是反向传播算法的核心
	3. ∂C/∂b<sup>l</sup><sub>j</sub>=δ<sup>l</sup><sub>j</sub>
		> C关于偏置b的偏导，与公式1思想一致，只不过1是关于神经元输入的
	4. ∂C/∂w<sup>l</sup><sub>jk</sub>=a<sup>l-1</sup><sub>k</sub> δ<sup>l</sup><sub>j</sub>
		> C关于每个w的偏导，3,4中已经涉及到我们需要求的参数
#### 代码实现
*	network类
	
		class Network(object):
		
		    def __init__(self, sizes): #sizes是个数组，分别表示每层网络神经元的个数
		        self.num_layers = len(sizes) #确定网络的层数
		        self.sizes = sizes #各层神经元个数的成员变量
				# randomn用于创建指定形状的数组，其中元素满足标准正态分布
                # biases中每一列元素的个数都与sizes对应位置元素值相同
		        self.biases = [np.random.randn(y, 1) for y in sizes[1:]]
				# zip用于合并列表生成矩阵，但要注意其对行列的处理
                # 如果sizes=[1,2,3]则sizes[:-1]=[1,2]，sizes[1:]=[2,3]，
				# zip(sizes[:-1],sizes[1:]) = [[1,2],[2,3]]
		        self.weights = [np.random.randn(y, x) 
		                        for x, y in zip(sizes[:-1], sizes[1:])]

*	sigmoid 函数和其导数

		def sigmoid(z):
		    return 1.0/(1.0+np.exp(-z))

		def sigmoid_prime(z):
		    """Derivative of the sigmoid function."""
		    return sigmoid(z)*(1-sigmoid(z))

*	forward 函数

	    def feedforward(self, a):
	        """Return the output of the network if "a" is input."""
			# 可以认为a是输入层的数据，即一张图片各个像素点的值数组
	        for b, w in zip(self.biases, self.weights):
	            a = sigmoid(np.dot(w, a)+b)
	        return a

*	backpropagation algorithm （反向传播算法）

*	SGD函数（随机梯度下降）

	    def SGD(self, training_data, epochs, mini_batch_size, eta, test_data=None):

	        """Train the neural network using mini-batch stochastic gradient descent.  
			The "training_data" is a list of tuples "(x, y)" representing the training 
			inputs and the desired outputs.  The other non-optional parameters are
	        self-explanatory.  If "test_data" is provided then the network will be 
			evaluated against the test data after each epoch, and partial progress 
			printed out.  This is useful for tracking progress, but slows things down 
			substantially."""

	        if test_data: n_test = len(test_data)
	        n = len(training_data)
	        for j in xrange(epochs):
	            random.shuffle(training_data)
				# 打乱训练数据；以mini_batch_size为步长选择子训练集
	            mini_batches = [training_data[k:k+mini_batch_size] for k in xrange(0, n, mini_batch_size)]
	            for mini_batch in mini_batches:
	                self.update_mini_batch(mini_batch, eta)
	            if test_data:
	                print "Epoch {0}: {1} / {2}".format(
	                    j, self.evaluate(test_data), n_test)
	            else:
	                print "Epoch {0} complete".format(j)

*	权值更新函数

	    def update_mini_batch(self, mini_batch, eta):

	        """Update the network's weights and biases by applying gradient descent using 
			backpropagation to a single mini batch.The "mini_batch" is a list of tuples "(x, y)", 
			and "eta" is the learning rate."""

	        nabla_b = [np.zeros(b.shape) for b in self.biases]
	        nabla_w = [np.zeros(w.shape) for w in self.weights]
	        for x, y in mini_batch:
	            delta_nabla_b, delta_nabla_w = self.backprop(x, y)
	            nabla_b = [nb+dnb for nb, dnb in zip(nabla_b, delta_nabla_b)]
	            nabla_w = [nw+dnw for nw, dnw in zip(nabla_w, delta_nabla_w)]
	        self.weights = [w-(eta/len(mini_batch))*nw for w, nw in zip(self.weights, nabla_w)]
	        self.biases = [b-(eta/len(mini_batch))*nb for b, nb in zip(self.biases, nabla_b)]

[1]:http://neuralnetworksanddeeplearning.com/