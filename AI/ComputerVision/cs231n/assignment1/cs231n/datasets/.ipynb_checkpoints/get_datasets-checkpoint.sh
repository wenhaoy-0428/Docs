if [ ! -d "cifar-10-batches-py" ]; then
  curl -o cifar-10-python.tar.gz http://www.cs.toronto.edu/~kriz/cifar-10-python.tar.gz 
  tar -xzvf cifar-10-python.tar.gz
  rm cifar-10-python.tar.gz
  curl -O http://cs231n.stanford.edu/imagenet_val_25.npz
fi
