#pragma once
#include <vector>


struct Sort
{
public:

	/// <summary>
	/// <para>�ׂ荇��2�̒l�̑召���r���������s��</para>
	/// <para>�v�f���̏��Ȃ��ȒP�ȃ��X�g�ŗp���邱�Ƃ��]�܂���</para>
	/// </summary>
	template <typename T>
	static void BubbleSort(T& data, const int dataSize)
	{
		//�z��̃T�C�Y - 1�񑀍�
		for (int i = 0; i < dataSize - 1; i++)
		{
			//�E����\�[�g�i��������ƕϐ���1������j
			for (int j = dataSize - 1; i < j; j--)
			{
				//���̐��l���傫���ꍇ�̂ݓ���ւ���
				if (data[j - 1] < data[j]) continue;
				Swap(&data[j], &data[j - 1]);
			}
		}
	}

	/// <summary>
	/// <para>�z��̍ŏ��l��T���擪�ƌ������s��</para>
	/// <para>�o�u���\�[�g��菈�����x������</para>
	/// </summary>
	template <typename T>
	static void SelectionSort(T& data, const int dataSize)
	{
		//�����珇�Ƀ\�[�g
		for (int i = 0; i < dataSize - 1; i++)
		{
			int min = i; //�ŏ��l,�����l�͖���̕����̐擪

			//����̕����̐擪����Ō�܂ł�T��
			for (int j = i + 1; j < dataSize; j++)
			{
				//�b��̍ŏ��l��菬�������l������ΕύX
				if (data[j] < data[min]) min = j;
			}
			//����ւ���i���̎��_�ōŏ��l�̗v�f�͔��ʍρj
			Swap(&data[i], &data[min]);
		}
	}

	/// <summary>
	/// <para>�l�Ԃ����ёւ����s�����̍l�����ɋ߂�</para>
	/// <para>�\�[�g�ς݂ɋ߂���Ώ������x�͑����A�t���ɕ���ł���ƒx���Ȃ�</para>
	/// </summary>
	template <typename T>
	static void InsertionSort(T& data, const int dataSize)
	{
		//���񂳂�Ă��Ȃ������̐擪���w��
		for (int i = 1; i < dataSize; i++)
		{
			// �����v�f�̂��߂̃C���f�b�N�X
			int j = i;

			// ����ς݂̏ꍇ�͏������Ȃ�
			while ((0 < j) && (data[j]) < data[j - 1])
			{
				// ���񂳂�Ă��Ȃ��ׂ荇���v�f����������
				Swap(&data[j - 1], &data[j]);

				// �ׂ荇���v�f�̃C���f�b�N�X���X�V
				j--;
			}
		}
	}

	/// <summary>
	/// <para>�S�̂��ׂ��������ď��������בւ��Ȃ��瓝������</para>
	/// <para>�}���\�[�g��菈�����x������</para>
	/// </summary>
	template <typename T>
	static void ShellSort(T& data, const int dataSize)
	{
		int powerNum = 0; //�Ԋu�p�ϐ�
		//�K�؂ȊԊu�̒T��
		while ((Pow(3, powerNum) - 1) / 2 < dataSize)
		{
			powerNum++;
		}
		
		int interval = (Pow(3, powerNum) - 1) / 2; //�Ԋu�̏����l
		bool flag = false; //�Ԋu1�̎��̔���p

		while (1 < interval || flag)
		{
			//�Ԋu�̕ύX
			if (1 < interval) interval = (interval - 1) / 3;
			//�t���O�̏�����
			flag = false;
			//�Ԋu�ŃO���[�v����
			for (int i = 0; i < dataSize - interval; i++)
			{			
				//�O���[�v���ɑ}���\�[�g�̎��{
				int temp = data[i + interval];
			
				//��r(1���)
				if(temp < data[i])
				{				
					int j = i; //�v�f�ԍ��̃R�s�[
					//�}���ꏊ�̒T��,�}���ꏊ���󂯂�(�}���n�_���E�̐���v�f��1�����炷)
					//�p������,����ϗv�f�ɑ}������v�f���l�̑傫���v�f������
					while (j + interval > 0 && data[j] > temp)
					{
						data[j + interval] = data[j]; //�v�f���Ԋu���E�ɂ��炷
						j -= interval; //���ׂ�v�f�����ɂ��炷
					}

					data[j + interval] = temp; //�}��
					flag = true;
				}
			}
		}
	}

	/// <summary>
	/// <para>��l�����ƂɃf�[�^�Q��2�ɕ�������ւ����J��Ԃ�</para>
	/// <para>�������x���������������̍ۂɓ����l�̏��Ԃ͕ۑ����ꂸ����\�[�g�ł͂Ȃ�</para>
	/// </summary>
	template <typename T>
	static void QuickSort(T& data, const int dataSize)
	{
		const int sortTop = 0;
		const int sortLast = dataSize - 1;
		QuickSort(data, sortTop, sortLast);
	}

	/// <summary>
	/// <para>�f�[�^�����ׂĂ΂炵�čēx���킹��ۂɕ��ѕς���</para>
	/// <para>�������x�������������f�[�^�̑��ɍ�Ɨp�̃f�[�^���g�p����</para>
	/// </summary>
	template <typename T>
	static void MergeSort(T& data, const int dataSize)
	{
		const int sortTop = 0;
		const int sortLast = dataSize - 1;
		T tempData = data;
		MergeSort(data, tempData, sortTop, sortLast);
	}

	/// <summary>
	/// <para>�q�[�v�\���𗘗p�����[�g�m�[�h�ɍő�l�i�ŏ��l�j������悤�ɂ��l�����Ɏ��o�����Ƃŕ��ѕς���</para>
	/// <para>�������x�������i�N�C�b�N�\�[�g�ɗ��j���������̍ۂɓ����l�̏��Ԃ͕ۑ����ꂸ����\�[�g�ł͂Ȃ�</para>
	/// </summary>
	template <typename T>
	static void HeapSort(T& data, const int dataSize)
	{
		int index = 0;

		//�q�[�v�\�z
		//�񕪖؂Ȃ̂Őe�m�[�h�̃C���f�b�N�X��
		//(n - 1) / 2 �ƂȂ�
		for (index = (dataSize - 1) / 2; 0 <= index; index--)
		{
			HeapSort(data, index, dataSize - 1);
		}

		//�q�[�v�\�[�g���s
		//�l�������ɕ��ׂ�B
		//
		//�擪�v�f(�ő�l)��z��̍Ō�Ɉړ�������
		//�Ō�̗v�f�𖳎����ăq�[�v���\�z�����
		//�z����ōł������Ȓl���珇�ɕ���
		for (index = dataSize - 1; 0 < index; index--)
		{
			const int temp = data[0];
			data[0] = data[index];
			data[index] = temp;
			HeapSort(data, 0, index - 1);
		}
	}

	/// <summary>
	/// <para>�f�[�^�̍ő�l�̒l���̃f�[�^�ɒl�����Ă������ѕς���</para>
	/// <para>����̎����ł͐����݂̂������ѕς����Ȃ�</para>
	/// </summary>
	template <typename T>
	static void BucketSort(T& data, const int dataSize)
	{
		//���ꕨ�̑傫�����f�[�^�̒l+1�ɂ���
		int bucketsSize = 0;
		for (int i = 0; i < dataSize; i++)
		{
			if (bucketsSize < data[i]) bucketsSize = data[i] + 1;
		}

		BucketSort(data, dataSize, bucketsSize);
	}

private:
	//�f�[�^�̓���ւ����s��
	template <typename T = int>
	static void Swap(T* leftData, T* rightData)
	{
		//�ꎞ�i�[
		const T temp = *leftData;

		//����ւ�
		*leftData = *rightData;
		*rightData = temp;
	}

	//�ݏ悵���l��Ԃ�
	template <typename T = int>
	[[nodiscard]] static const int Pow(T num, T power)
	{
		int powerNum = num;
		for (int i = 0; i < power; i++)
		{
			powerNum = powerNum * num;
		}
		return powerNum;
	}

	//�����l�T��(�N�C�b�N�\�[�g�����ŗ��p)
	template <typename T = int>
	[[nodiscard]] static const int SearchMiddle(const T top, const T middle, const T last)
	{
		//�擪�������l
		if ((top < middle && top > last) || (top < last && top > middle)) return top;
		//�����������l
		else if ((top < middle && middle < last) || (top > middle && middle > last)) return middle;
		//���̑�(����������l�ł͂Ȃ��ꍇ���܂�)
		else return last;
	}

	//�N�C�b�N�\�[�g(�N�C�b�N�\�[�g�����ŗ��p)
	template <typename T1, typename T2 = int>
	static void QuickSort(T1& data, const T2 top, const T2 last)
	{
		T2 topIndex = top, lastIndex = last;

		const T2 middleIndex = topIndex + (lastIndex - topIndex) / 2;
		//3�_�̒����l����Ƃ���
		const T2 pivot = SearchMiddle(data[topIndex], data[middleIndex], data[lastIndex]);

		//���[�v����(1�x�̃��[�v��2��������)
		while (true)
		{
			//����傫�Ȓl��擪����T��
			while (data[topIndex] < pivot) topIndex++; //�T���ʒu�����炷

			//���菬���Ȓl���Ōォ��T��
			while (data[lastIndex] > pivot) lastIndex--; //�T���ʒu�����炷

			//����ւ���K�v���Ȃ��Ȃ�΃��[�v�𔲂���(i��j�̈ʒu�֌W�������Ȃ�΃��[�v�𔲂���)
			if (lastIndex - 1 < topIndex) break;

			//�z��̓���ւ����s��
			Swap(&data[topIndex], &data[lastIndex]);

			//�X���b�v���s�Ȃ����ꍇ�͈͂�������߂�(�X���b�v�����ꏊ��T�����Ȃ���)�ĒT��
			topIndex++;
			lastIndex--;
		}

		//2���������͈͂����ꂼ��ōX�ɕ�������(�ċA�I�ɌJ��Ԃ�)
		if (top < topIndex - 1) RecurseQuick(data, top, topIndex - 1);
		if (lastIndex + 1 < last) RecurseQuick(data, lastIndex + 1, last);
	}

	//�ċA���邽�߂̌Ăяo��
	template <typename T1, typename T2 = int>
	static void RecurseQuick(T1& data, const T2 top, const T2 last)
	{
		QuickSort(data, top, last);
	}

	//�}�[�W�\�[�g
	template <typename T>
	static void MergeSort(T& data, T& tempData, const int start, const int end)
	{
		if (end <= start) return;

		//start��end�̒��Ԓn�_�𕪊��_�Ƃ���
		const int middle = (start + end) / 2;
		//�O���������ċA�I�ɐ���
		MergeSort(data, tempData, start, middle);
		//�㔼�������ċA�I�ɐ���
		MergeSort(data, tempData, middle + 1, end);
		//��Ɨp�̃f�[�^
		int left = 0, right = 0, index = 0;
		//���z�̈�̃f�[�^���}�[�W���Ȃ���R�s�[����
		for (left = start; left <= middle; left++)
		{
			tempData[index] = data[left];
			index++;
		}
		for (right = end; middle + 1 <= right; right--)
		{
			tempData[index] = data[right];
			index++;
		}
		//���[����f�[�^���擾���āA�}�[�W���Ă���
		left = 0;
		right = end - start;
		for (index = start; index <= end; index++)
		{
			if (tempData[left] <= tempData[right])
			{
				data[index] = tempData[left];
				left++;
			}
			else
			{
				data[index] = tempData[right];
				right--;
			}
		}
	}

	//�q�[�v�\�[�g
	template <typename T>
	void HeapSort(T& data, const int root, const int bottom)
	{
		// �q�m�[�h�̃C���f�b�N�X
		int child = (2 * root) + 1;

		// �e�m�[�h�̒l��ێ����Ă���
		const int temp = data[root];

		while (child <= bottom)
		{
			//�񕪖؂̂ӂ��̎q�m�[�h����l���傫���ق��̎q�m�[�h��I������
			if (child < bottom && data[child] < data[child + 1]) child = child + 1;

			//�e�m�[�h�̒l���q�m�[�h�̒l�ȉ��̏ꍇ����ւ���
			if (data[child] < temp) break;

			data[(child - 1) / 2] = data[child];
			//�q�m�[�h�̃C���f�b�N�X��i�߂�
			child = (2 * child) + 1;
		}
		// �e�m�[�h�ƂȂ�v�f�ɒl������
		data[(child - 1) / 2] = temp;
	}

	//�ċA���邽�߂̌Ăяo��
	template <typename T>
	void RecurseHeap(T& data, const int root, const int bottom)
	{
		//�q�m�[�h�̃C���f�b�N�X
		//�z��̐擪�v�f�̃C���f�b�N�X�� 0 �Ȃ̂�
		//�q�m�[�h�� 2n + 1 �� 2n + 2 �Ōv�Z����
		int left = (root * 2) + 1;
		int right = (root * 2) + 2;

		//�ő�l�����v�f�̃C���f�b�N�X
		int maxChild = 0;

		if (left <= bottom && data[root] < data[left]) maxChild = left;
		else maxChild = root;

		if (right <= bottom && data[maxChild] < data[right]) maxChild = right;

		if (maxChild != root)
		{
			const int temp = data[root];
			data[root] = data[maxChild];
			data[maxChild] = temp;
			//�z��̐擪�v�f�ɂ͍ő�l�����v�f�̃C���f�b�N�X���w�肷��
			RecurseHeap(data, maxChild, bottom);
		}
	}

	//�o�P�b�g�\�[�g
	template <typename T>
	static void BucketSort(T& data, const int dataSize, int bucketsSize)
	{
		T buckets(bucketsSize);
		for (int i = 0; i < bucketsSize; i++)
		{
			buckets[i] = 0;
		}

		//���̃f�[�^���o�P�b�g�ɓ����
		for (int i = 0; i < dataSize; i++)
		{
			buckets[data[i]] = data[i];
		}
		//�z��̃C���f�b�N�X
		int index = 0;
		//�o�P�b�g���猳�̔z��ɖ߂�
		for (int i = 0; i < bucketsSize; i++)
		{
			if (0 < buckets[i]) data[index++] = buckets[i];
		}
	}
};