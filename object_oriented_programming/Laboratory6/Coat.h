#pragma once
#include <string>

class Coat
{
private:
	int size;
	std::string color;
	int price;
	int quant;
	std::string link;

public:	
	/// <summary>
	/// Initializes a new instance of the <see cref="Coat"/> class.
	/// </summary>
	/// <param name="size">The size.</param>
	/// <param name="color">The color.</param>
	/// <param name="price">The price.</param>
	/// <param name="quant">The quant.</param>
	/// <param name="link">The link.</param>
	Coat(int const &size, std::string const &color, int const &price, int const &quant, std::string const &link);
	
	/// <summary>
	/// Copy constructor for the <see cref="Coat"/> class.
	/// </summary>
	/// <param name="c">The c.</param>
	Coat(Coat &c);
	
	/// <summary>
	/// Operator=s the specified coat.
	/// </summary>
	/// <param name="c">The coat.</param>
	/// <returns>A copy of the given coat.</returns>
	Coat& operator=(Coat &c);
	
	/// <summary>
	/// Finalizes an instance of the <see cref="Coat"/> class.
	/// </summary>
	~Coat();
	
	/// <summary>
	/// Gets the size.
	/// </summary>
	/// <returns>Integer, the size.</returns>
	int getSize() const;
	
	/// <summary>
	/// Gets the color.
	/// </summary>
	/// <returns>String, the color.</returns>
	std::string getColor() const;
	
	/// <summary>
	/// Gets the price.
	/// </summary>
	/// <returns>Integer, the price.</returns>
	int getPrice() const;
	
	/// <summary>
	/// Gets the quantity.
	/// </summary>
	/// <returns>Integer, the quantity.</returns>
	int getQuant() const;
	
	/// <summary>
	/// Gets the link.
	/// </summary>
	/// <returns>String, the link</returns>
	std::string getLink() const;
	
	/// <summary>
	/// Sets the size.
	/// </summary>
	/// <param name="size">The size.</param>
	void setSize(int const &size);
	
	/// <summary>
	/// Sets the color.
	/// </summary>
	/// <param name="color">The color.</param>
	void setColor(std::string const &color);
	
	/// <summary>
	/// Sets the price.
	/// </summary>
	/// <param name="price">The price.</param>
	void setPrice(int const &price);
	
	/// <summary>
	/// Sets the quantity.
	/// </summary>
	/// <param name="quant">The quant.</param>
	void setQuant(int const &quant);
	
	/// <summary>
	/// Sets the link.
	/// </summary>
	/// <param name="link">The link.</param>
	void setLink(std::string const &link);
	
	/// <summary>
	/// Operator==s the <see cref="Coat"/> class.
	/// </summary>
	/// <param name="c2">The second coat</param>
	/// <returns></returns>
	bool operator==(Coat const &c2);
	
	/// <summary>
	/// Shows the photo.
	/// </summary>
	void showPhoto();
	
	/// <summary>
	/// Decreases the quantity by 1.
	/// </summary>
	void decreaseQuant();
	
	/// <summary>
	/// Increases the quantity by 1.
	/// </summary>
	void increaseQuant();
	
	static int coatCount;
	
	/// <summary>
	/// Gets the count of the initialized objects.
	/// </summary>
	/// <returns>Integer.</returns>
	int getCount();
};
