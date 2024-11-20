import os #文件和目录操作
import matplotlib.pyplot as plt #导入Matplotlib库的pyplot模块，用于绘图
import torch #导入PyTorch库，用于深度学习模型的构建和训练。
import torch.nn as nn #导入PyTorch的神经网络模块，用于定义神经网络层
import torch.optim as optim #导入PyTorch的优化器模块，用于优化神经网络的参数
from torch.utils.data import DataLoader #导入PyTorch的数据加载器模块，用于批量加载数据
from torchvision import datasets, transforms, utils #导入torchvision库的数据集、数据变换和工具模块，用于处理图像数据


# 定义生成器
class Generator(nn.Module):# 定义生成器类，继承自nn.Module
    def __init__(self, input_size, hidden_dim, output_size): #初始化生成器，定义输入、隐藏层和输出的大小
        super(Generator, self).__init__() # 调用父类nn.Module的初始化函数
        self.main = nn.Sequential( #使用nn.Sequential定义生成器的网络结构，包括三层全连接层和激活函数。
            nn.Linear(input_size, hidden_dim), #将输入的特征映射到隐藏层
            nn.ReLU(True),# 激活函数f(x) = max(0,x)
            nn.Linear(hidden_dim, hidden_dim), #将隐藏层的特征重新映射到隐藏层
            nn.ReLU(True),# 激活函数f(x) = max(0,x)
            nn.Linear(hidden_dim, output_size),#将隐藏层的特征映射到输出层
            nn.Tanh() #归一化数据，确保生成的图像像素值在[-1,1]范围
        )

    def forward(self, x): # 定义前向传播函数，将输入数据通过上面的网络结构进行计算并返回输出
        return self.main(x)


# 定义判别器
class Discriminator(nn.Module): #定义判别器类，继承自nn.Module
    def __init__(self, input_size, hidden_dim, output_size): #初始化判别器，定义输入、隐藏层和输出的大小
        super(Discriminator, self).__init__() #调用父类nn.Module的初始化函数
        self.main = nn.Sequential(
            nn.Linear(input_size, hidden_dim), #输入层->隐藏层
            nn.LeakyReLU(0.2, inplace=True), # f(x) = max(0.2 * x, x)
            nn.Linear(hidden_dim, hidden_dim),#隐藏层->隐藏层
            nn.LeakyReLU(0.2, inplace=True), # f(x) = max(0.2 * x, x)
            nn.Linear(hidden_dim, output_size),#隐藏层->输出层
            nn.Sigmoid() # 1/(1+e^(-x))，归一化到[0,1]
        )

    def forward(self, x):
        return self.main(x)


# 超参数设置
batch_size = 100  #设置每次训练的批量大小
learning_rate = 0.0002  #学习率
num_epochs = 50  #训练次数
z_dim = 100  #设置生成器输入的噪声向量的维度
hidden_dim = 256  #设置隐藏层的神经元数量
image_size = 28 * 28  #设置图像的大小（MNIST图像为28x28像素）

# 数据加载和预处理
transform = transforms.Compose([ #定义数据预处理操作，包括将图像转换为张量和归一化处理
    transforms.ToTensor(), #将图像数据转换为PyTorch张量
    transforms.Normalize((0.5,), (0.5,)) #[0,1] -->  -0.5 /0.5 --> [-1,1]
])

mnist = datasets.MNIST(root='./data', train=True, transform=transform, download=True) #下载并加载MNIST数据集，应用预处理操作
dataloader = DataLoader(mnist, batch_size=batch_size, shuffle=True) #使用DataLoader批量加载数据集，并在每个epoch打乱数据

# 初始化生成器和判别器
G = Generator(z_dim, hidden_dim, image_size)
D = Discriminator(image_size, hidden_dim, 1)

# 损失函数和优化器
criterion = nn.BCELoss() # 定义二元交叉熵损失函数
optimizer_G = optim.Adam(G.parameters(), lr=learning_rate) #定义生成器的Adam优化器
optimizer_D = optim.Adam(D.parameters(), lr=learning_rate) #定义判别器的Adam优化器

# 创建保存生成图像的文件夹
os.makedirs('gan_images', exist_ok=True)


# 训练GAN
# 绘制并保存生成的图像
def save_image(images, path):
    images = images / 2 + 0.5  # 数据反归一化到[0,1]
    grid = utils.make_grid(images) # 将图像张量转换为网格图像
    plt.imshow(grid.numpy().transpose((1, 2, 0))) #显示图像
    plt.savefig(path) #保存图像到指定的位置


for epoch in range(num_epochs): #训练num_epochs次
    for i, (images, _) in enumerate(dataloader): #加载每个批次的数据
        # 训练判别器
        real_images = images.view(-1, image_size) # 将真实图像数据展平
        real_labels = torch.ones(batch_size, 1) # 创建真实标签，全为1
        fake_labels = torch.zeros(batch_size, 1) # 创建假标签，全为0

        outputs = D(real_images) # 判别器对真实图像的输出
        d_loss_real = criterion(outputs, real_labels) # 计算判别器对真实图像的损失
        real_score = outputs #保存评分

        z = torch.randn(batch_size, z_dim) #生成随机噪声向量
        fake_images = G(z) #生成假图像
        outputs = D(fake_images.detach()) #将生成的假图像输入判别器 D，冻结生成器的梯度
        d_loss_fake = criterion(outputs, fake_labels) #计算假图像损失
        fake_score = outputs #计算假图像评分

        d_loss = d_loss_real + d_loss_fake #计算总损失。目标是同时提高判别器区分真实图像和假图像的能力
        optimizer_D.zero_grad() # 清空判别器的梯度
        d_loss.backward() # 反向传播计算损失的梯度
        optimizer_D.step() # 用优化器更新判别器的参数

        # 训练生成器
        z = torch.randn(batch_size, z_dim) #生成新的随机噪声向量
        fake_images = G(z) #生成新的假图像
        outputs = D(fake_images) #判别器输出
        g_loss = criterion(outputs, real_labels)  #计算损失函数

        optimizer_G.zero_grad() # 清空判别器的梯度
        g_loss.backward()# 反向传播计算损失的梯度
        optimizer_G.step()# 用优化器更新判别器的参数

        if (i + 1) % 200 == 0: #每两百次打印一次训练的信息
            print(
                f'Epoch [{epoch}/{num_epochs}], Step [{i + 1}/{len(dataloader)}], d_loss: {d_loss.item():.4f}, g_loss: {g_loss.item():.4f}, D(x): {real_score.mean().item():.4f}, D(G(z)): {fake_score.mean().item():.4f}')

    # 保存生成的图像
    fake_images = fake_images.view(fake_images.size(0), 1, 28, 28)
    save_image(fake_images, f'gan_images/fake_images-{epoch + 1}.png')

print('训练完成。')

