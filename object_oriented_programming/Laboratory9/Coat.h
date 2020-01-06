#pragma once
#include <string>

class Coat
{
	unsigned int size;
	std::string colour;
	unsigned int price;
	unsigned int quantity;
	std::string photo;

public:	
	/// <summary>
	/// Initializes a new instance of the <see cref="Coat"/> class.
	/// </summary>
	Coat();
			
	/// <summary>
	/// Copy constructor for the <see cref="Coat"/> class.
	/// </summary>
	/// <param name="c">The original <see cref="Coat"/> instance.</param>
	Coat(const Coat &c);

	/// <summary>
	/// Initializes a new instance of the <see cref="Coat"/> class.
	/// </summary>
	/// <param name="size">Unsigned int, the size.</param>
	/// <param name="colour">String, the colour.</param>
	/// <param name="price">Unsigned int, the price.</param>
	/// <param name="quantity">Unsigned int, the quantity.</param>
	/// <param name="photo">String, the photo.</param>
	Coat(const unsigned int &size, const std::string &colour, const unsigned int &price, const unsigned int &quantity, const std::string &photo);
		
	/// <summary>
	/// Finalizes an instance of the <see cref="Coat"/> class.
	/// </summary>
	~Coat();
	
	/// <summary>
	/// Overloads the equality check operator for <see cref="Coat"/> instances. Compares the size and the colour.
	/// </summary>
	/// <param name="c">The second <see cref="Coat"/> instance to be verified.</param>
	/// <returns>Boolean, true if the <see cref="Coat"/> instances hace the same size and colout, false otherwise</returns>
	bool operator==(const Coat &c);	

	/// <summary>
	/// Overloads the assignment operator for <see cref="Coat"/> instances.
	/// </summary>
	/// <param name="c">The <see cref="Coat"/> instance given.</param>
	/// <returns>A new <see cref="Coat"/> instance with the same values as the given one.</returns>
	Coat &operator=(const Coat &c);

#pragma region getters	
	/// <summary>
	/// Gets the size of the current <see cref="Coat"/> instance.
	/// </summary>
	/// <returns>Unsigned integer, the size of the current <see cref="Coat"/> instance.</returns>
	unsigned int getSize() const { return this->size; }

	/// <summary>
	/// Gets the colour of the current <see cref="Coat"/> instance.
	/// </summary>
	/// <returns>String, the colour of the current <see cref="Coat"/> instance.</returns>
	std::string getColour() const { return this->colour; }
		
	/// <summary>
	/// Gets the price of the current <see cref="Coat"> instance.
	/// </summary>
	/// <returns>Unsigned integer, the price of the current <see cref="Coat"/> instance.</returns>
	unsigned int getPrice() const { return this->price; }
	
	/// <summary>
	/// Gets the quantity of the current <see cref="Coat"> instance.
	/// </summary>
	/// <returns>Unsigned integer, the quantity of the current <see cref="Coat"/> instance.</returns>
	unsigned int getQuantity() const { return this->quantity; }
	
	/// <summary>
	/// Gets the photo of the current <see cref="Coat"/> instance.
	/// </summary>
	/// <returns>String, the photo of the current <see cref="Coat"/> instance.</returns>
	std::string getPhoto() const { return this->photo; }
#pragma endregion

#pragma region setters	
	/// <summary>
	/// Sets the size of the current <see cref="Coat"/> instance.
	/// </summary>
	/// <param name="size">Integer, the size.</param>
	void setSize(const unsigned int &size);
	
	/// <summary>
	/// Sets the colour of the current <see cref="Coat"/> instance.
	/// </summary>
	/// <param name="colour">String, the colour.</param>
	void setColour(const std::string &colour);
	
	/// <summary>
	/// Sets the price of the current <see cref="Coat"/> instance.
	/// </summary>
	/// <param name="price">Unsigned int, the price.</param>
	void setPrice(const unsigned int &price);
	
	/// <summary>
	/// Sets the quantity of the current <see cref="Coat"/> instance.
	/// </summary>
	/// <param name="quantity">Unsigned integer, the quantity.</param>
	void setQuantity(const unsigned int &quantity);
	
	/// <summary>
	/// Increases the quantity of the current <see cref="Coat"/> instance by 1.
	/// </summary>
	void increaseQuantity();
	
	/// <summary>
	/// Decreases the quantity of the current <see cref="Coat"/> instance by 1.
	/// </summary>
	void decreaseQuantity();
	
	/// <summary>
	/// Sets the photo of the current <see cref="Coat"/> instance.
	/// </summary>
	/// <param name="photo">String, the photo.</param>
	void setPhoto(const std::string &photo);
#pragma endregion	
	/// <summary>
	/// Opens the photo in Chrome browser.
	/// </summary>
	void showPhoto();

	/// <summary>
	/// Overloads the >> operator for input streams and <see cref="Coat"/> instances.
	/// </summary>
	friend std::istream& operator>>(std::istream& is, Coat &c);
	
	/// <summary>
	/// Overloads the << operator for output streams and <see cref="Coat"/> instances.
	/// </summary/>
	friend std::ostream& operator<<(std::ostream& os, const Coat &c);
};